/*
 * Movement.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */

#include "TimeLimitedAction.h"
#include "SetterAction.h"

TimeLimitedAction::TimeLimitedAction(): currentDuration(0.0) {
	// TODO Auto-generated constructor stub

}

TimeLimitedAction::~TimeLimitedAction() {
	// TODO Auto-generated destructor stub
}

void TimeLimitedAction::init(Channel* channel, double duration, double delay,
				std::vector<Incrementer*> incrementers,
				std::vector<Incrementer*> decrementers){
	StimulationAction::init(channel);
	setDuration(duration);
	setDelay(delay);
	if(incrementers.size() != 2){
		throw new stim::errors::TwoIncrementersException(incrementers.size());
	}
	if(decrementers.size() != 2){
		throw new stim::errors::TwoDecrementersException(decrementers.size());
	}
	setCurrentIncrementer(incrementers[0]);
	setPulseWidthIncrementer(incrementers[1]);
	setCurrentDecrementer(decrementers[0]);
	setPulseWidthDecrementer(decrementers[1]);
}

float TimeLimitedAction::getPulseWidthIncrement(double& dt) {
	float pulseWidthIncrement(0);
	if (currentDuration - delay < pulseWidthIncrementer->getDuration() ||
			(currentDuration - delay >= 0 && !pulseWidthIncrementer->calledOnce())) {
		pulseWidthIncrement = pulseWidthIncrementer->getIncrement(dt, channel->getPulseWidth());
	} else if (currentDuration - delay >= duration - pulseWidthDecrementer->getDuration() ||
			(currentDuration - delay +dt >= duration && !pulseWidthDecrementer->calledOnce())) {
		pulseWidthIncrement = pulseWidthDecrementer->getDecrement(dt, channel->getPulseWidth());
	}
	return pulseWidthIncrement;
}

float TimeLimitedAction::getCurrentIncrement(double& dt) {
	float currentIncrement(0);
	if (currentDuration - delay < currentIncrementer->getDuration() ||
			(currentDuration - delay >= 0 && !currentIncrementer->calledOnce())) {
		currentIncrement = currentIncrementer->getIncrement(dt, channel->getCurrent());
	} else if (currentDuration - delay >= duration - currentDecrementer->getDuration() ||
			(currentDuration - delay + dt >= duration && !currentDecrementer->calledOnce())) {
		currentIncrement = currentDecrementer->getDecrement(dt, channel->getCurrent());
	}
	return currentIncrement;
}

bool TimeLimitedAction::setChannelParameters(double& dt) {
	float currentIncrement = getCurrentIncrement(dt);
	float pulseWidthIncrement = getPulseWidthIncrement(dt);
	channel->setPulseWidth(channel->getPulseWidth() + pulseWidthIncrement);
	channel->setCurrent(channel->getCurrent() + currentIncrement);

	return currentIncrement != 0 || pulseWidthIncrement != 0;
}

void TimeLimitedAction::update(double dt){
	if(stimulating){
		if(currentDuration >= delay){
			bool shouldUpdate = setChannelParameters(dt);
			if(shouldUpdate){
				channel->update();
			}
		}
		currentDuration += dt;
		if(currentDuration >= duration + delay){
			currentDuration = duration + delay + dt;
			stimulating = false;
			channel->stop();
		}
	}
}

void TimeLimitedAction::setDuration(double nDuration){
	duration = nDuration >= 0 ? nDuration : duration;
}

void TimeLimitedAction::setDelay(double nDelay){
	delay = nDelay >= 0 ? nDelay : delay;
}

void TimeLimitedAction::setCurrentIncrementer(Incrementer* nIncrementer){
	if(nIncrementer == nullptr){
		throw new stim::errors::NullptrIncrementerException();
	}

	currentIncrementer = nIncrementer;
}

void TimeLimitedAction::setPulseWidthIncrementer(Incrementer* nIncrementer){
	if(nIncrementer == nullptr){
		throw new stim::errors::NullptrIncrementerException();
	}
	pulseWidthIncrementer = nIncrementer;
}

void TimeLimitedAction::setCurrentDecrementer(Incrementer* nDecrementer){
	if(nDecrementer == nullptr){
		throw new stim::errors::NullptrIncrementerException();
	}
	currentDecrementer = nDecrementer;
}

void TimeLimitedAction::setPulseWidthDecrementer(Incrementer* nDecrementer){
	if(nDecrementer == nullptr){
		throw new stim::errors::NullptrIncrementerException();
	}
	pulseWidthDecrementer = nDecrementer;
}

std::vector<double> TimeLimitedAction::getStimulationPattern(double timeStep){
	return TimeLimitedAction::getStimulationPattern(duration, delay, {currentIncrementer, pulseWidthIncrementer},
			{currentDecrementer, pulseWidthDecrementer}, timeStep);
}

std::vector<double> TimeLimitedAction::getStimulationPattern(double duration,
		double delay,
		std::vector<Incrementer*> incrementers,
		std::vector<Incrementer*> decrementers,
		double timeStep){
	std::vector<double> pattern;
	for(int i(0); i < (delay + duration)/timeStep; ++i){
		pattern.push_back(0);
	}
	return pattern;
}

bool TimeLimitedAction::areSimultaneousActions(StimulationAction* action){
	return action->areSimultaneousActions(this);
}

bool TimeLimitedAction::areSimultaneousActions(TimeLimitedAction* action){
	if(action->getChannel()->getChannelNumber() == getChannel()->getChannelNumber()
		&& ((action->getDelay() < getDelay() && action->getDuration() + action->getDelay() > getDelay()) ||
				(action->getDelay() > getDelay() && getDuration() + getDelay() > action->getDelay()))){
		return true;
	}
	return false;
}

bool TimeLimitedAction::areSimultaneousActions(SetterAction* action){
	if(action->getChannel()->getChannelNumber() == getChannel()->getChannelNumber() &&
			getDelay() == 0){
		return true;
	}
	return false;
}
