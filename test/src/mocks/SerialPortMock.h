/*
 * SerialPortMock.h
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */
#pragma once
#include "../../../src/interfaces/SerialPort.h"
#include "gmock/gmock.h"


class SerialPortMock: public SerialPort{
public:
	MOCK_METHOD1(spInit, void(sp_tty*));
	MOCK_METHOD3(spOpen, int(sp_tty*, const char*, int));
	MOCK_METHOD1(spClose, void(sp_tty*));
	MOCK_METHOD2(spWaitr, int(sp_tty*, fl_reply*));
	MOCK_METHOD2(spWritem, ssize_t(sp_tty*, const fl_message*));
};


