#pragma once
#include <jsoncpp/json/json.h>
#include "Channel.h"
#include "Incrementer.h"

class TimeLimitedAction;
class SetterAction;

class StimulationAction{
protected:
	Channel* channel;
	bool stimulating;

public:

	StimulationAction();
	virtual ~StimulationAction(){}

	virtual void update(double dt){}
	virtual void init(Channel* channel);

	virtual Channel* getChannel(){return channel;}

	virtual void stimulate();
	virtual bool isStimulating(){return stimulating;}
	virtual bool areSimultaneousActions(StimulationAction* action){return false;}
	virtual bool areSimultaneousActions(TimeLimitedAction* action){return false;}
	virtual bool areSimultaneousActions(SetterAction* action){return false;}


protected:
	void setChannel(Channel* nChannel);

};
