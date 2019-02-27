/*
 * ChannelMock.h
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "../../../src/Channel.h"
#include "gmock/gmock.h"

class ChannelMock: public Channel{
public:
	ChannelMock(): Channel(new sp_tty(), new SerialPort(), 1, false){}
	ChannelMock(sp_tty* dev, SerialPort* port, int nbChannel, bool channel):Channel(dev, port, nbChannel, false){}
	MOCK_METHOD2(init, void(double,double));
	MOCK_METHOD0(update, void());
	MOCK_METHOD0(stop,void());

	MOCK_METHOD1(setCurrent, void(double));
	MOCK_METHOD1(setPulseWidth, void(double));

	MOCK_METHOD0(getChannelNumber, int());
	MOCK_METHOD0(getCurrent,double());
	MOCK_METHOD0(getPulseWidth,double());
};
