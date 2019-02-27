/*
 * SetterAction.h
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */

#pragma once

#include "StimulationAction.h"

class TimeLimitedAction;

class SetterAction: public StimulationAction {
public:
	SetterAction();
	virtual ~SetterAction();
	virtual void init(Channel* channel, int current, float pulseWidth);
	virtual void update(double dt);

	virtual int getCurrent(){return current;}
	virtual float getPulseWidth(){return pulseWidth;}
	virtual bool areSimultaneousActions(StimulationAction* action);
	virtual bool areSimultaneousActions(TimeLimitedAction* action);
	virtual bool areSimultaneousActions(SetterAction* action);


private:
	int current;
	float pulseWidth;
};

