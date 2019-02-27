/*
 * MovementTestCase.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */
#include "../../src/TimeLimitedAction.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mocks/ChannelMock.h"
#include "mocks/IncrementerMock.h"
#include "../../src/SetterAction.h"


class TimeLimitedActionTest : public ::testing::Test{
public:
	TimeLimitedActionTest(){
		action = new TimeLimitedAction();
		channel = new ChannelMock();
	}
	~TimeLimitedActionTest(){
		delete action;
		delete channel;
		delete currentIncrementer;
		delete pulseWidthIncrementer;
		delete currentDecrementer;
		delete pulseWidthDecrementer;
	}
	void initTest();

	TimeLimitedAction* action;
	ChannelMock* channel;
	double duration; //ms
	double delay; //ms
	IncrementerMock* currentIncrementer;
	IncrementerMock* pulseWidthIncrementer;
	IncrementerMock* currentDecrementer;
	IncrementerMock* pulseWidthDecrementer;
	Json::Value parameters;

};

void TimeLimitedActionTest::initTest(){
	duration = 5; //ms
	delay = 0; //ms
	currentIncrementer = new IncrementerMock();
	pulseWidthIncrementer = new IncrementerMock();
	currentDecrementer = new IncrementerMock();
	pulseWidthDecrementer = new IncrementerMock();
}

TEST_F(TimeLimitedActionTest, InitWithEmptyChannelShouldThrow){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	EXPECT_THROW(action->init(nullptr, duration, delay,  incrementers, decrementers), std::exception*);
}

TEST_F(TimeLimitedActionTest, InitWithWrongNumberOfIncrementersShouldThrow){
	initTest();
	std::vector<Incrementer*> incrementers = {pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	EXPECT_THROW(action->init(channel, duration, delay,  incrementers, decrementers), std::exception*);
}

TEST_F(TimeLimitedActionTest, InitWithWrongNumberOfDecrementersShouldThrow){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer};
	EXPECT_THROW(action->init(channel, duration, delay,  incrementers, decrementers), std::exception*);
}


TEST_F(TimeLimitedActionTest, InitWithEmptyIncrementerShouldThrow){
	initTest();
	std::vector<Incrementer*> incrementers = {nullptr, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	EXPECT_THROW(action->init(channel, duration, delay,  incrementers, decrementers), std::exception*);
}

TEST_F(TimeLimitedActionTest, InitACtionWithVectorOfIncrementersSuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	action->init(channel, duration, delay, incrementers, decrementers);
}

TEST_F(TimeLimitedActionTest, ActionInitSuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	action->init(channel, duration, delay,  incrementers, decrementers);

	ASSERT_EQ(action->getChannel(), channel);
	ASSERT_EQ(action->getDuration(), duration);
	ASSERT_EQ(action->getDelay(), delay);
}

TEST_F(TimeLimitedActionTest, StimulateOneStepSuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	action->init(channel, duration, delay,  incrementers, decrementers);
	action->stimulate();
	EXPECT_TRUE(action->isStimulating());
}

TEST_F(TimeLimitedActionTest, StimulateRampCurrentPulseWidthWithDelayWithNullDurationSuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);

	EXPECT_CALL(*channel, update()).Times(2);
	EXPECT_CALL(*currentIncrementer, calledOnce()).Times(12).WillOnce(::testing::Return(false)).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*currentIncrementer, getDuration()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*currentDecrementer, calledOnce()).Times(1).WillOnce(::testing::Return(false));
	EXPECT_CALL(*currentDecrementer, getDuration()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*pulseWidthIncrementer, calledOnce()).Times(12).WillOnce(::testing::Return(false)).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*pulseWidthIncrementer, getDuration()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*pulseWidthDecrementer, calledOnce()).Times(1).WillOnce(::testing::Return(false));
	EXPECT_CALL(*pulseWidthDecrementer, getDuration()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*currentIncrementer, getIncrement(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(0.5));
	EXPECT_CALL(*pulseWidthIncrementer, getIncrement(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(0.5));
	EXPECT_CALL(*currentDecrementer, getDecrement(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(-0.5));
	EXPECT_CALL(*pulseWidthDecrementer, getDecrement(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(-0.5));
	EXPECT_CALL(*channel, getCurrent()).Times(14);
	EXPECT_CALL(*channel, getPulseWidth()).Times(14);
	EXPECT_CALL(*channel, setCurrent(::testing::_)).Times(12);
	EXPECT_CALL(*channel, setPulseWidth(::testing::_)).Times(12);
	EXPECT_CALL(*channel, stop()).Times(1);

	action->stimulate();
	for(int i(0); i < 18; ++i){
		action->update(1);
	}
	ASSERT_EQ(action->getCurrentDuration(),duration+delay+1);
}

TEST_F(TimeLimitedActionTest, StimulateRampCurrentPulseWidthWithDelaySuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);

	EXPECT_CALL(*channel, update()).Times(10);
	EXPECT_CALL(*currentIncrementer, calledOnce()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*currentIncrementer, getDuration()).WillRepeatedly(::testing::Return(5));
	EXPECT_CALL(*pulseWidthIncrementer, calledOnce()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*pulseWidthIncrementer, getDuration()).WillRepeatedly(::testing::Return(5));
	EXPECT_CALL(*currentDecrementer, getDuration()).WillRepeatedly(::testing::Return(5));
	EXPECT_CALL(*pulseWidthDecrementer, getDuration()).WillRepeatedly(::testing::Return(5));
	EXPECT_CALL(*currentIncrementer, getIncrement(::testing::_,::testing::_)).Times(5).WillRepeatedly(::testing::Return(0.5));
	EXPECT_CALL(*currentDecrementer, getDecrement(::testing::_,::testing::_)).Times(5).WillRepeatedly(::testing::Return(0.5));
	EXPECT_CALL(*pulseWidthIncrementer, getIncrement(::testing::_,::testing::_)).Times(5).WillRepeatedly(::testing::Return(0.5));
	EXPECT_CALL(*pulseWidthDecrementer, getDecrement(::testing::_,::testing::_)).Times(5).WillRepeatedly(::testing::Return(0.5));
	EXPECT_CALL(*channel, getCurrent()).Times(22);
	EXPECT_CALL(*channel, getPulseWidth()).Times(22);
	EXPECT_CALL(*channel, setCurrent(::testing::_)).Times(12);
	EXPECT_CALL(*channel, setPulseWidth(::testing::_)).Times(12);
	EXPECT_CALL(*channel, stop()).Times(1);

	action->stimulate();
	for(int i(0); i < 20; ++i){
		action->update(1);
	}
	ASSERT_EQ(action->isStimulating(),false);
	ASSERT_EQ(action->getCurrentDuration(),duration+delay+1);
}

TEST_F(TimeLimitedActionTest, GetStimulationPatternSuccess){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	double timeStep = 0.1;
	action->init(channel, duration, delay,  incrementers, decrementers);
	std::vector<double> pattern = action->getStimulationPattern(timeStep);
	ASSERT_EQ(pattern.size(), (delay + duration) / timeStep);
}

TEST_F(TimeLimitedActionTest, SimultaneousActionsShouldReturnTrue){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);
	TimeLimitedAction* action2 = new TimeLimitedAction();
	delay = 5;
	duration = 4;
	action2->init(channel, duration, delay,  incrementers, decrementers);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_TRUE(action->areSimultaneousActions(action2));
}

TEST_F(TimeLimitedActionTest, OverlappingActionsShouldReturnTrue){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);
	TimeLimitedAction* action2 = new TimeLimitedAction();
	delay = 5;
	duration = 15;
	action2->init(channel, duration, delay,  incrementers, decrementers);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_TRUE(action->areSimultaneousActions(action2));
}

TEST_F(TimeLimitedActionTest, NonSimultaneousActionsShouldReturnFalse){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 4;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);
	TimeLimitedAction* action2 = new TimeLimitedAction();
	delay = 16.5;
	duration = 4;
	action2->init(channel, duration, delay,  incrementers, decrementers);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_FALSE(action->areSimultaneousActions(action2));
}

TEST_F(TimeLimitedActionTest, SimultaneousActionsWithSetterShouldReturnTrue){
	initTest();
	std::vector<Incrementer*> incrementers = {currentIncrementer, pulseWidthIncrementer};
	std::vector<Incrementer*> decrementers = {currentDecrementer, pulseWidthDecrementer};
	delay = 0;
	duration = 12;
	action->init(channel, duration, delay,  incrementers, decrementers);
	SetterAction* action2 = new SetterAction();
	action2->init(channel, 0, 0);
	EXPECT_CALL(*channel, getChannelNumber()).Times(2);
	EXPECT_TRUE(action->areSimultaneousActions(action2));
}

TEST_F(TimeLimitedActionTest, NonSimultaneousActionsWithSetterShouldReturnFalse){
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
}
