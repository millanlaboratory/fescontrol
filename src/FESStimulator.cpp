/*
 * FESStimulator.cpp
 *
 *  Created on: Oct 2, 2017
 *      Author: cnbiadministrator
 */

#include "FESStimulator.h"
#include "errors/StimulationException.h"
#include <vector>
#include <iostream>
#include <algorithm>    // std::remove_if

bool FESStimulator::tryDifferentUSBToConnect() {
	for (int usbPort(0); usbPort < 8; ++usbPort) {
		std::string usbPortName = "/dev/ttyUSB" + std::to_string(usbPort);
		if(verbose){
			std::cerr << "Try connecting to " << usbPortName << ": ";
		}
		if (serialPort->spOpen(device, usbPortName.c_str(), usbPort) > 0) {
			return true;
		}
		if(verbose){
			std::cerr << "\033[1;31mFailure\033[0m" << std::endl;
		}
	}
	return false;
}

void FESStimulator::tryConnectingToStimDevice() {
	serialPort->spInit(device);
	bool couldConnect = tryDifferentUSBToConnect();
	if (!couldConnect) {
		throw new stim::errors::StimulatorException();
	}
	else if(verbose){
		std::cerr << "\033[1;32mSuccess\033[1;0m" << std::endl;
	}
}

FESStimulator::FESStimulator(bool nVerbose): serialPort(nullptr), verbose(nVerbose){
	setFrequency(25);
}

void FESStimulator::destroyChannels() {
	for (unsigned int i(0); i < channels.size(); ++i) {
		channels[i]->stop();
		channels[i]->update();
		delete channels[i];
	}
}

FESStimulator::~FESStimulator() {
	destroyChannels();
	removeAllActions();
	if(serialPort != nullptr){
		serialPort->spClose(device);
		delete serialPort;
	}
}

void FESStimulator::init(SerialPort* nSerialPort, sp_tty* nDevice){
	serialPort = nSerialPort;
	device = nDevice;
	tryConnectingToStimDevice();
}

void FESStimulator::addChannel(Channel* channel){
	if(channel == nullptr){
		throw new stim::errors::NullPtrActionException();
	}
	channels.push_back(channel);
}

void FESStimulator::addStimulationAction(StimulationAction* action){
	if(action == nullptr){
		throw new stim::errors::NullPtrActionException();
	}
	actions.push_back(action);
}

void FESStimulator::removeAllActions(){
	for(unsigned int i(0); i < actions.size(); ++i){
		delete actions[i];
	}
	actions.clear();
}

void FESStimulator::updateDeviceFrequency() {
	fl_message message;
	fl_reply reply;
	fl_setfrequency(&message, (fl_tbyte)((int)frequency));
	serialPort->spWritem(device, &message);
	int answer = serialPort->spWaitr(device, &reply);
	if(answer != FESREPLY_RECVOK) {
		if(answer == FESREPLY_SENDAGAIN){
			if(verbose){
				std::cerr << "Command rejected " << std::endl;
				std::cerr << "Frequency : " << (int)frequency << std::endl;
			}
			updateDeviceFrequency();
		}
		else{
			throw new stim::errors::StimulatorFrequencyException(frequency);
		}
	}
}

void FESStimulator::setFrequency(double nFrequency){
	if(nFrequency < 0){
		throw new stim::errors::StimulatorFrequencyException(nFrequency);
	}
	frequency = nFrequency;
}

void FESStimulator::start(){
	updateDeviceFrequency();
	for(unsigned int i(0); i < actions.size(); ++i){
		actions[i]->stimulate();
	}
}

void FESStimulator::resetChannels(){
	for(unsigned int i(0); i < channels.size(); ++i){
		channels[i]->stop();
		channels[i]->update();
	}
}

void FESStimulator::update(float dt){
	for(unsigned int i(0); i < actions.size(); ++i){
		actions[i]->update(dt);
		if(!actions[i]->isStimulating()){
			delete actions[i];
			actions[i] = nullptr;
		}
	}
	actions.erase(std::remove(actions.begin(), actions.end(), nullptr), actions.end());
}

bool FESStimulator::areActionsComplete(){
	return actions.size() == 0;
}

Channel* FESStimulator::getChannelByChannelNumber(int channelNumber){
	for(unsigned int channelIndex(0); channelIndex < channels.size(); ++channelIndex){
		if(channels[channelIndex]->getChannelNumber() == channelNumber){
			return channels[channelIndex];
		}
	}
	throw new stim::errors::ChannelNotInStimulatorException(channelNumber);
}


