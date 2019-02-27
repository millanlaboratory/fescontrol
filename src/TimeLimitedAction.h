/*
 * Movement.h
 *
 *  Created on: Dec 15, 2017
 *      Author: cnbi
 */
#pragma once

#include "StimulationAction.h"
#include "errors/StimulationException.h"
#include "LinearIncrementer.h"

class SetterAction;

class TimeLimitedAction: public StimulationAction{
public:
	TimeLimitedAction();
	virtual ~TimeLimitedAction();

	virtual void init(Channel* channel, double duration, double delay,
				std::vector<Incrementer*> incrementers,
				std::vector<Incrementer*> decrementers);

	virtual void update(double dt);

	virtual double getDuration(){return duration;}
	virtual double getCurrentDuration(){return currentDuration;}
	virtual double getDelay(){return delay;}
	Incrementer* getCurrentIncrementer(){return currentIncrementer;}
	Incrementer* getPulseWidthIncrementer(){return pulseWidthIncrementer;}
	Incrementer* getCurrentDecrementer(){return currentDecrementer;}
	Incrementer* getPulseWidthDecrementer(){return pulseWidthDecrementer;}
	bool setChannelParameters(double& dt);
	virtual bool areSimultaneousActions(StimulationAction* action);
	virtual bool areSimultaneousActions(TimeLimitedAction* action);
	virtual bool areSimultaneousActions(SetterAction* action);

	double getLinearIncrease(int minValue, int maxValue, int duration, double dt);
	std::vector<double> getStimulationPattern(double timeStep);
	static std::vector<double> getStimulationPattern(
			double duration,
			double delay,
			std::vector<Incrementer*> incrementers,
			std::vector<Incrementer*> decrementers,
			double timeStep);

private:
	double duration; //ms
	double delay; //ms
	double currentDuration;
	Incrementer* currentIncrementer;
	Incrementer* pulseWidthIncrementer;
	Incrementer* currentDecrementer;
	Incrementer* pulseWidthDecrementer;
	float getCurrentIncrement(double& dt);
	float getPulseWidthIncrement(double& dt);

	void setDuration(double nDuration);
	void setDelay(double nDelay);
	void setCurrentIncrementer(Incrementer* nIncrementer);
	void setPulseWidthIncrementer(Incrementer* nIncrementer);
	void setCurrentDecrementer(Incrementer* nDecrementer);
	void setPulseWidthDecrementer(Incrementer* nDecrementer);
};

