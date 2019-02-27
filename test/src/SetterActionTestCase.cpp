/*
 * SetterActionTestCase.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */

#include "../../src/SetterAction.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/ChannelMock.h"
#include "../../src/TimeLimitedAction.h"


class TimeLimitedActionMock: public TimeLimitedAction{
public:
	MOCK_METHOD0(getChannel, Channel*());
	MOCK_METHOD0(getDelay, double());
};

class SetterActionTest : public ::testing::Test{
public:
	SetterActionTest(){
		action = new SetterAction();
		channel = new ChannelMock();
	}
	~SetterActionTest(){
		delete action;
		delete channel;
	}
	void initTest();

	SetterAction* action;
	int current;
	double pulseWidth;
	ChannelMock* channel;
	Json::Value parameters;
};

void SetterActionTest::initTest(){
	current = 5;
	pulseWidth = 0.5;
}

TEST_F(SetterActionTest, InitWithEmptyChannelShouldThrow){
	initTest();
	EXPECT_THROW(action->init(nullptr, current, pulseWidth), std::exception*);
}

TEST_F(SetterActionTest, InitWithNegativeCurrentShouldThrow){
	initTest();
	EXPECT_THROW(action->init(channel, -1, pulseWidth), std::exception*);
}

TEST_F(SetterActionTest, InitWithNegativePulseWidthShouldThrow){
	initTest();
	EXPECT_THROW(action->init(channel, current, -1), std::exception*);
}

TEST_F(SetterActionTest, ActionInitSuccess){
	initTest();
	action->init(channel, current, pulseWidth);

	ASSERT_EQ(action->getChannel(), channel);
	ASSERT_EQ(action->getCurrent(), current);
	ASSERT_EQ(action->getPulseWidth(), pulseWidth);
}

TEST_F(SetterActionTest, UpdateActionSeveralTimesExpectChannelToBeUpdatedOnce){
	initTest();
	action->init(channel, current, pulseWidth);
	EXPECT_CALL(*channel, setCurrent(::testing::_)).Times(1);
	EXPECT_CALL(*channel, setPulseWidth(::testing::_)).Times(1);
	EXPECT_CALL(*channel, update()).Times(1);
	action->stimulate();
	int maxIterations(5);
	float dt(0.01);
	for(int i(0); i < maxIterations; ++i){
		action->update(dt);
	}
}

TEST_F(SetterActionTest, SimultaneousActionsShouldReturnTrue){
	initTest();
	action->init(channel, current, pulseWidth);
	SetterAction* action2 = new SetterAction();
	action2->init(channel, current, pulseWidth);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_TRUE(action->areSimultaneousActions(action2));
}

TEST_F(SetterActionTest, SimultaneousActionsWithTimeLimitedShouldReturnTrue){
	initTest();
	action->init(channel, current, pulseWidth);
	TimeLimitedActionMock* action2 = new TimeLimitedActionMock();
	EXPECT_CALL(*channel, getChannelNumber()).Times(2).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*action2, getChannel()).WillOnce(::testing::Return(channel));
	EXPECT_CALL(*action2, getDelay()).WillOnce(::testing::Return(0.0));
	EXPECT_TRUE(action->areSimultaneousActions(action2));
	delete action2;
}

/*TEST_F(SetterActionTest, NonSimultaneousActionsWithLimitedShouldReturnFalse){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 3;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);
	SetterAction* action2 = new SetterAction();
	action2->init(channel, 0, 0);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_FALSE(action->areSimultaneousActions(action2));
}*/

