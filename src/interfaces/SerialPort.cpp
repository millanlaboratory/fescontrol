/*
 * SerialPort.cpp
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */

#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort() {
	// TODO Auto-generated constructor stub

}

SerialPort::~SerialPort() {
	// TODO Auto-generated destructor stub
}

void SerialPort::spInit(sp_tty* device){
	sp_init(device);
}
int SerialPort::spOpen(sp_tty* device, const char* name, int async){
	return sp_open(device, name, async);
}
ssize_t SerialPort::spWritechar(sp_tty* device, const unsigned char* byte){
	return sp_writechar(device, byte);
}
ssize_t SerialPort::spWrite(sp_tty* device, const void* buffer, size_t bsize){
	return sp_write(device, buffer, bsize);
}
ssize_t SerialPort::spWritem(sp_tty* device, const fl_message* message){
	return sp_writem(device, message);
}
ssize_t SerialPort::spRead(sp_tty* device, void* buffer, size_t bsize){
	return sp_read(device, buffer, bsize);
}
ssize_t SerialPort::spReadm(sp_tty* device, fl_message* message){
	return sp_readm(device, message);
}
ssize_t SerialPort::spReadr(sp_tty* device, fl_reply* reply){
	return sp_readr(device, reply);
}
void SerialPort::spClose(sp_tty* device){
	sp_close(device);
}
int SerialPort::spWaitr(sp_tty* device, fl_reply* reply){
	return sp_waitr(device, reply);
}
void SerialPort::spDisplay(void){
	sp_display();
}
