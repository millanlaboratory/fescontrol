#include <gmock/gmock.h>

#include "../../src/Channel.h"
#include "mocks/SerialPortMock.h"

class ChannelTestCase: public ::testing::Test{
public:
	ChannelTestCase(): channelNumber(5), current(2), pulseWidth(205), verbose(false), tty(new sp_tty()),
	serialPortMock(new SerialPortMock()){
		sp_init(tty);
		channel = new Channel(tty, serialPortMock, channelNumber, verbose);
	}
	~ChannelTestCase(){
		delete tty;
		delete serialPortMock;
	}

	int channelNumber;
	Channel* channel;
	int current;
	int pulseWidth;
	bool verbose;
	sp_tty* tty;
	SerialPortMock* serialPortMock;
};


TEST_F(ChannelTestCase, ChannelCreationFailure){
	int channelNumber = -1;
	EXPECT_THROW(new Channel(tty, serialPortMock, channelNumber, verbose), channel::errors::ChannelException*);
}

TEST_F(ChannelTestCase, ChannelCreationFailureWithNullptrThrow){
	EXPECT_THROW(new Channel(nullptr, serialPortMock, channelNumber, verbose), channel::errors::TtyException*);
}

TEST_F(ChannelTestCase, ChannelCreationFailureWithSErialPortNullptrThrow){
	EXPECT_THROW(new Channel(tty, nullptr, channelNumber, verbose), channel::errors::SerialPortException*);
}

TEST_F(ChannelTestCase, ChannelInitializationFailureWithNegativeCurrent){
	EXPECT_THROW(channel->init(-1, 205), channel::errors::ChannelParameterException*);
}

TEST_F(ChannelTestCase, ChannelInitializationFailureWithTooHighCurrent){
	EXPECT_THROW(channel->init(65, 205), channel::errors::ChannelParameterException*);
}

TEST_F(ChannelTestCase, ChannelInitializationFailureWithWrongPulseWidth){
	EXPECT_THROW(channel->init(1, -400), channel::errors::ChannelParameterException*);
}

TEST_F(ChannelTestCase, ChannelCreationSuccess){
	channel->init(current, pulseWidth);
	ASSERT_EQ(channel->getChannelNumber(), channelNumber);
	ASSERT_EQ(channel->getCurrent(), current);
	ASSERT_EQ(channel->getPulseWidth(), pulseWidth);
}

TEST_F(ChannelTestCase, WorkingUpdate){
	EXPECT_CALL(*serialPortMock, spWaitr(::testing::_,::testing::_)).Times(1).WillRepeatedly(::testing::Return(FESREPLY_RECVOK));
	EXPECT_CALL(*serialPortMock, spWritem(::testing::_,::testing::_)).Times(1);
	channel->init(current, pulseWidth);
	channel->update();
}

TEST_F(ChannelTestCase, UpdatingStimulatorRequireToSendCommandAgain){
	EXPECT_CALL(*serialPortMock, spWaitr(::testing::_,::testing::_)).Times(2).
			WillOnce(::testing::Return(FESREPLY_SENDAGAIN)).WillOnce(::testing::Return(FESREPLY_RECVOK));
	EXPECT_CALL(*serialPortMock, spWritem(::testing::_,::testing::_)).Times(2);
	channel->init(current, pulseWidth);
	channel->update();
}


TEST_F(ChannelTestCase, CannotUpdateStimulatorShouldThrow){
	EXPECT_CALL(*serialPortMock, spWaitr(::testing::_,::testing::_)).Times(1).WillRepeatedly(::testing::Return(FESREPLY_REJECTED));
	EXPECT_CALL(*serialPortMock, spWritem(::testing::_,::testing::_)).Times(1);
	channel->init(current, pulseWidth);
	EXPECT_THROW(channel->update(), channel::errors::StimulationException*);
}

TEST_F(ChannelTestCase, StopSuccess){
	EXPECT_CALL(*serialPortMock, spWaitr(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(FESREPLY_RECVOK));
	EXPECT_CALL(*serialPortMock, spWritem(::testing::_,::testing::_)).Times(1);
	channel->init(current, pulseWidth);
	channel->stop();
	channel->update();
	ASSERT_EQ(channel->getCurrent(), 0);
}
