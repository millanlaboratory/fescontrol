/*
 * SetterAction.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */

#include "SetterAction.h"
#include "errors/StimulationException.h"
#include "TimeLimitedAction.h"

SetterAction::SetterAction(): current(0), pulseWidth(0.0) {
	// TODO Auto-generated constructor stub

}

SetterAction::~SetterAction() {
	// TODO Auto-generated destructor stub
}

void SetterAction::init(Channel* channel, int nCurrent, float nPulseWidth){
	StimulationAction::init(channel);
	if(nCurrent < 0){
		throw new stim::errors::NegativeCurrentException();
	}
	if(nPulseWidth < 0){
		throw new stim::errors::NegativePulseWidthException();
	}
	current = nCurrent;
	pulseWidth = nPulseWidth;
}

void SetterAction::update(double dt){
	if(stimulating){
		channel->setCurrent(current);
		channel->setPulseWidth(pulseWidth);
		channel->update();
		stimulating = false;
	}

}

bool SetterAction::areSimultaneousActions(StimulationAction* action){
	return action->areSimultaneousActions(this);
}

bool SetterAction::areSimultaneousActions(TimeLimitedAction* action){
	if(action->getChannel()->getChannelNumber() == getChannel()->getChannelNumber() &&
			action->getDelay() == 0){
		return true;
	}
	return false;
}

bool SetterAction::areSimultaneousActions(SetterAction* action){
	if(action->getChannel()->getChannelNumber() == getChannel()->getChannelNumber()){
		return true;
	}
	return false;
}
