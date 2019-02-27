/*
 * SerialPort.h
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "serialport.h"

class SerialPort {
public:
	SerialPort();
	virtual ~SerialPort();

	virtual void spInit(sp_tty* device);
	virtual int spOpen(sp_tty* device, const char* name, int async);
	virtual ssize_t spWritechar(sp_tty* device, const unsigned char* byte);
	virtual ssize_t spWrite(sp_tty* device, const void* buffer, size_t bsize);
	virtual ssize_t spWritem(sp_tty* device, const fl_message* message);
	virtual ssize_t spRead(sp_tty* device, void* buffer, size_t bsize);
	virtual ssize_t spReadm(sp_tty* device, fl_message* message);
	virtual ssize_t spReadr(sp_tty* device, fl_reply* reply);
	virtual void spClose(sp_tty* device);
	virtual int spWaitr(sp_tty* device, fl_reply* reply);
	virtual void spDisplay(void);
};

