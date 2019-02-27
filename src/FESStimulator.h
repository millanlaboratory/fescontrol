/*
 * FESStimulator.h
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include <vector>
#include "Channel.h"
#include "StimulationAction.h"
#include "interfaces/SerialPort.h"

#define CHANNELS_QUANTITY 8

class FESStimulator {
public:
	FESStimulator(bool verbose = false);
	virtual ~FESStimulator();
	std::vector<Channel*> getChannels(){return channels;}
	std::vector<StimulationAction*> getStimulationActions() {return actions;}
	double getFrequency(){return frequency;}
	virtual void addStimulationAction(StimulationAction* action);
	virtual void removeAllActions();
	virtual void addChannel(Channel* channel);
	virtual void setFrequency(double nFrequency);
	virtual void init(SerialPort* nSerialPort, sp_tty* nDevice);
	virtual void start();
	virtual void resetChannels();
	virtual void update(float dt);
	virtual bool areActionsComplete();
	virtual Channel* getChannelByChannelNumber(int channelNumber);


private:
	std::vector<StimulationAction*> actions;
	std::vector<Channel*> channels;
	sp_tty* device;
	SerialPort* serialPort;
	double frequency;
	bool verbose;

	void updateDeviceFrequency();
	void destroyChannels();
	bool tryDifferentUSBToConnect();
	void tryConnectingToStimDevice();
};

