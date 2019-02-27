#pragma once

#include "errors/ChannelException.h"
#include "interfaces/SerialPort.h"
#include "fesencode.h"
#include "fesdecode.h"

#define FIRST_CHANNEL 1
#define LAST_CHANNEL 8

#define MAX_CURRENT 35

class Channel{
public:
	Channel(sp_tty* nTeleTypeWriter, SerialPort* serialPort, int nChannelNumber, bool verbose);
	virtual ~Channel(){}
	virtual void init(double current, double pulseWidth);
	virtual void update();
	virtual void stop();

	virtual int getChannelNumber(){return channelNumber;}
	virtual double getCurrent(){return current;}
	virtual double getPulseWidth(){return pulseWidth;}

	virtual void setCurrent(double nCurrent);
	virtual void setPulseWidth(double nPulseWidth);

private:
	void setChannelNumber(int nChannelNumber);
	void setTTY(sp_tty* nTeleTypeWriter);
	void setSerialPort(SerialPort* nSerialPort);

	int channelNumber;
	double current;
	double pulseWidth;
	sp_tty* teleTypeWriter;
	SerialPort* serialPort;
	bool verbose;
};
