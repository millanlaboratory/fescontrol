/*
 * FESStimulatorTest.cpp
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */
#include "gmock/gmock.h"
#include "../../src/errors/StimulationException.h"
#include "../../src/FESStimulator.h"
#include "mocks/SerialPortMock.h"
#include "mocks/StimulationActionMock.h"
#include "mocks/ChannelMock.h"

using ::testing::Return;

class FESStimulatorTestCase: public ::testing::Test{
public:
	FESStimulatorTestCase():
		serialMock(new SerialPortMock()),
		actionMock(new StimulationActionMock()),
		stimulator(new FESStimulator()),
		device(new sp_tty()){
		for(int i (0); i < 8; ++i){
			channels.push_back(new ChannelMock(device, serialMock, i+1, false));
		}
	}
	~FESStimulatorTestCase(){
		delete stimulator;
	}
	void expectCreationSuccess(){
		EXPECT_CALL(*serialMock, spInit(::testing::_)).Times(1);
		EXPECT_CALL(*serialMock, spOpen(::testing::_,::testing::_,::testing::_)).Times(1).WillOnce(Return(true));
		EXPECT_CALL(*serialMock, spClose(::testing::_)).Times(1);
	}

	void expectStimulatorFrequencyUpdate(){
		EXPECT_CALL(*serialMock, spWaitr(::testing::_,::testing::_)).Times(1).WillRepeatedly(::testing::Return(FESREPLY_RECVOK));
		EXPECT_CALL(*serialMock, spWritem(::testing::_,::testing::_)).Times(1);
	}
	SerialPortMock* serialMock;
	StimulationActionMock* actionMock;
	FESStimulator* stimulator;
	std::vector<ChannelMock*> channels;
	sp_tty* device;
};

TEST_F(FESStimulatorTestCase, creationNoUSBFailureShouldThrow){
	EXPECT_CALL(*serialMock, spInit(::testing::_)).Times(1);
	EXPECT_CALL(*serialMock, spOpen(::testing::_,::testing::_,::testing::_)).Times(8);
	EXPECT_CALL(*serialMock, spClose(::testing::_)).Times(1);
	ASSERT_THROW(stimulator->init(serialMock, new sp_tty()), stim::errors::StimulatorException*);
	delete actionMock;
}

TEST_F(FESStimulatorTestCase, creationSuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());

	ASSERT_EQ(stimulator->getChannels().size(), 0);
	ASSERT_EQ(stimulator->getStimulationActions().size(), 0);
}

TEST_F(FESStimulatorTestCase, UpdatingStimulatorRequireToSendCommandAgain){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->setFrequency(25);
	EXPECT_CALL(*serialMock, spWaitr(::testing::_,::testing::_)).Times(2).
			WillOnce(::testing::Return(FESREPLY_SENDAGAIN)).
			WillOnce(::testing::Return(FESREPLY_RECVOK));
	EXPECT_CALL(*serialMock, spWritem(::testing::_,::testing::_)).Times(2);
	stimulator->start();
}

TEST_F(FESStimulatorTestCase, CannotUpdateStimulatorFrequencyShouldThrow){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->setFrequency(25);
	EXPECT_CALL(*serialMock, spWaitr(::testing::_,::testing::_)).Times(1).
			WillOnce(::testing::Return(FESREPLY_REJECTED));
	EXPECT_CALL(*serialMock, spWritem(::testing::_,::testing::_)).Times(1);
	EXPECT_THROW(stimulator->start(), stim::errors::StimulatorFrequencyException*);
}

TEST_F(FESStimulatorTestCase, SetNegativeFrequencyShouldThrow){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	EXPECT_THROW(stimulator->setFrequency(-1), stim::errors::StimulatorFrequencyException*);
}

TEST_F(FESStimulatorTestCase, setFrequencySuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->setFrequency(25);
	ASSERT_EQ(stimulator->getFrequency(), 25);
}

TEST_F(FESStimulatorTestCase, RemoveAllActionsSuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->addStimulationAction(actionMock);
	stimulator->removeAllActions();
	ASSERT_EQ(stimulator->getStimulationActions().size(), 0);
}

TEST_F(FESStimulatorTestCase, ResetChannelsExpectAllChannelsToZero){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	EXPECT_CALL(*channels[0], stop()).Times(2);
	EXPECT_CALL(*channels[0], update()).Times(2);
	stimulator->addChannel(channels[0]);
	stimulator->resetChannels();

	ASSERT_EQ(stimulator->getStimulationActions().size(), 0);
}

TEST_F(FESStimulatorTestCase, addActionSuccessExpectIncrement){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->addStimulationAction(actionMock);
	ASSERT_EQ(stimulator->getStimulationActions().size(), 1);
}

TEST_F(FESStimulatorTestCase, addChannelExpectIncrement){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->addChannel(channels[0]);
	EXPECT_CALL(*channels[0], stop()).Times(1);
	EXPECT_CALL(*channels[0], update()).Times(1);
	ASSERT_EQ(stimulator->getChannels().size(), 1);
}

TEST_F(FESStimulatorTestCase, addNullPtrActionExpectThrow){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	EXPECT_THROW(stimulator->addStimulationAction(nullptr), stim::errors::NullPtrActionException*);
}

TEST_F(FESStimulatorTestCase, updateStimulatorSuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->addStimulationAction(actionMock);
	EXPECT_CALL(*actionMock, stimulate()).Times(1);
	EXPECT_CALL(*actionMock, update(::testing::_)).Times(1);
	EXPECT_CALL(*actionMock, isStimulating()).Times(1).WillOnce(::testing::Return(true));
	expectStimulatorFrequencyUpdate();
	stimulator->start();
	stimulator->update(0.75);
	ASSERT_EQ(stimulator->areActionsComplete(), false);
}

TEST_F(FESStimulatorTestCase, destroyCompletedActionsSuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	stimulator->addStimulationAction(actionMock);
	EXPECT_CALL(*actionMock, stimulate()).Times(1);
	EXPECT_CALL(*actionMock, update(::testing::_)).Times(2);
	EXPECT_CALL(*actionMock, isStimulating()).Times(2).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));
	expectStimulatorFrequencyUpdate();
	for(unsigned int i (0); i < channels.size(); ++i){
		stimulator->addChannel(channels[i]);
		EXPECT_CALL(*channels[i], stop()).Times(1);
		EXPECT_CALL(*channels[i], update()).Times(1);
	}
	stimulator->start();
	stimulator->update(0.75);
	stimulator->update(0.75);
	ASSERT_EQ(stimulator->getStimulationActions().size(), 0);
	ASSERT_EQ(stimulator->areActionsComplete(), true);
}

TEST_F(FESStimulatorTestCase, getChannelByChannelNumberSuccess){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	for(unsigned int i (0); i < channels.size(); ++i){
		EXPECT_CALL(*channels[i], stop()).Times(1);
		EXPECT_CALL(*channels[i], update()).Times(1);
		stimulator->addChannel(channels[i]);
	}
	EXPECT_CALL(*channels[0], getChannelNumber()).Times(2).WillRepeatedly(::testing::Return(5));
	ASSERT_EQ(stimulator->getChannelByChannelNumber(5)->getChannelNumber(), 5);
}

TEST_F(FESStimulatorTestCase, getChannelByWrongChannelNumberShouldThrow){
	expectCreationSuccess();
	stimulator->init(serialMock, new sp_tty());
	ASSERT_THROW(stimulator->getChannelByChannelNumber(9)->getChannelNumber(), stim::errors::ChannelNotInStimulatorException*);
}
