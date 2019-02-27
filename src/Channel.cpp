#include "Channel.h"


Channel::Channel(sp_tty* nTeleTypeWriter, SerialPort* serialPort, int nChannelNumber, bool nVerbose):
	current(0), pulseWidth(0), verbose(nVerbose){
	setChannelNumber(nChannelNumber);
	setTTY(nTeleTypeWriter);
	setSerialPort(serialPort);
}

void Channel::init(double nCurrent, double nPulseWidth){
	setCurrent(nCurrent);
	setPulseWidth(nPulseWidth);
}

void Channel::setChannelNumber(int nChannelNumber){
	if(nChannelNumber < FIRST_CHANNEL or nChannelNumber > LAST_CHANNEL){
		throw new channel::errors::ChannelException();
	}
	channelNumber = nChannelNumber;
}

void Channel::setTTY(sp_tty* nTeleTypeWriter){
	if(nTeleTypeWriter == nullptr){
		throw new channel::errors::TtyException();
	}
	teleTypeWriter = nTeleTypeWriter;
}

void Channel::setSerialPort(SerialPort* nSerialPort){
	if(nSerialPort == nullptr){
		throw new channel::errors::SerialPortException();
	}
	serialPort = nSerialPort;
}

void Channel::setCurrent(double nCurrent){
	//std::cerr << "Current " << getCurrent() << std::endl;

	if(nCurrent < 0 || nCurrent > MAX_CURRENT){
		throw new channel::errors::ChannelParameterException(nCurrent);
	}
	current = nCurrent;
}

void Channel::setPulseWidth(double nPulseWidth){
	//std::cerr << "PW " << getPulseWidth() << std::endl;

	if(nPulseWidth < 0){
		throw new channel::errors::ChannelParameterException(nPulseWidth);
	}
	pulseWidth = nPulseWidth;
}

void Channel::update(){
	fl_message message;
	fl_reply reply;
	fl_activate(&message, (unsigned int)channelNumber, current == 0 ? 1 : (fl_tbyte)((int)current), pulseWidth == 0 ? 0 : ((int)(pulseWidth*1000))/1000.0);
	serialPort->spWritem(teleTypeWriter, &message);
	int answer = serialPort->spWaitr(teleTypeWriter, &reply);
	if(answer != FESREPLY_RECVOK) {
		if(answer == FESREPLY_SENDAGAIN){
			if(verbose){
				std::cerr << "Command rejected " << std::endl;
				std::cerr << "Channel : " << ((int)current) << std::endl;
				std::cerr << "Current : " << ((int)current) << std::endl;
				std::cerr << "PulseWidth : " << ((int)(pulseWidth*1000))/1000.0<< std::endl;
			}
			update();
		}
		else{
			throw new channel::errors::StimulationException();
		}
	}
}

void Channel::stop(){
	current = 0;
	pulseWidth = 0;
}
