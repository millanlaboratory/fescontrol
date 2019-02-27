/*
 * StimulationActionFactory.h
 *
 *  Created on: Dec 18, 2017
 *      Author: cnbi
 */

#pragma once
#include "StimulationAction.h"
#include "TimeLimitedAction.h"
#include "IncrementerFactory.h"
#include "FESStimulator.h"
#include "SetterAction.h"
#include <jsoncpp/json/json.h>


class StimulationActionFactory {
public:
	StimulationActionFactory();
	virtual void init(FESStimulator* stimulator, IncrementerFactory* nfactory);
	virtual StimulationAction* createStimulationActionFromJson(Json::Value* json);
	virtual ~StimulationActionFactory();

	FESStimulator* getStimulator(){return stimulator;}
	IncrementerFactory* getIncrementerFactory(){return factory;}
	virtual void throwIfBadGrammar(Json::Value* action);

private:
	IncrementerFactory* factory;
	FESStimulator* stimulator;

	std::vector<Incrementer*> generateDecrementers(Json::Value& jsonAction);
	std::vector<Incrementer*> generateIncrementers(Json::Value& jsonAction);
	std::vector<double> tryExtractingParametersFromJson(Json::Value& obj);
	void throwIfBadTimeLimitedActionGrammar(Json::Value& action);
	void throwIfBadSetterActionGrammar(Json::Value& json);
	SetterAction* tryCreatingSetterAction(Json::Value& json);
	TimeLimitedAction* tryCreatingTimeLimitedAction(Json::Value& json);
};

