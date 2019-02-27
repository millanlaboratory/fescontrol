/*
 * StimulationActionFactory.cpp
 *
 *  Created on: Dec 18, 2017
 *      Author: cnbi
 */

#include "StimulationActionFactory.h"
#include "errors/JsonException.h"


StimulationActionFactory::StimulationActionFactory() {
	// TODO Auto-generated constructor stub

}

StimulationActionFactory::~StimulationActionFactory() {
	delete factory;
}

void StimulationActionFactory::init(FESStimulator* nStimulator, IncrementerFactory* nFactory){
	stimulator = nStimulator;
	factory = nFactory;
}

StimulationAction* StimulationActionFactory::createStimulationActionFromJson(Json::Value* json){
	if((*json)["actionType"].asString() == "limited"){
		TimeLimitedAction* action = tryCreatingTimeLimitedAction(*json);
		return action;
	}
	else if((*json)["actionType"].asString() == "setter"){
		SetterAction* action = tryCreatingSetterAction(*json);
		return action;
	}
	throw new json::errors::BadGrammarException("file");
}

std::vector<double> StimulationActionFactory::tryExtractingParametersFromJson(Json::Value& obj) {
	std::vector<double> parameters;
	for (unsigned int paramIndex(0); paramIndex < obj.size();++paramIndex) {
		parameters.push_back(obj[paramIndex].asDouble());
	}
	return parameters;
}

SetterAction* StimulationActionFactory::tryCreatingSetterAction(
		Json::Value& json) {
	throwIfBadSetterActionGrammar(json);
	SetterAction* action = new SetterAction();
	action->init(stimulator->getChannelByChannelNumber(json["channel"].asInt()),
			json["current"].asInt(), json["pulseWidth"].asDouble());
	return action;
}

TimeLimitedAction* StimulationActionFactory::tryCreatingTimeLimitedAction(
		Json::Value& json) {
	throwIfBadTimeLimitedActionGrammar(json);
	TimeLimitedAction* action = new TimeLimitedAction();
	action->init(stimulator->getChannelByChannelNumber(json["channel"].asInt()),
			json["duration"].asDouble(), json["delay"].asDouble(),
			generateIncrementers(json), generateDecrementers(json));
	return action;
}

std::vector<Incrementer*> StimulationActionFactory::generateDecrementers(Json::Value& jsonAction){
	std::vector<Incrementer*> incrementers;
	incrementers.push_back(factory->createIncrementerFromString(
			jsonAction["currentDecrementMode"].asString(),
			tryExtractingParametersFromJson(jsonAction["currentDecrementerParameters"])));
	incrementers.push_back(factory->createIncrementerFromString(
			jsonAction["pulseWidthDecrementMode"].asString(),
			tryExtractingParametersFromJson(jsonAction["pulseWidthDecrementerParameters"])));
	return incrementers;
}

std::vector<Incrementer*> StimulationActionFactory::generateIncrementers(Json::Value& jsonAction){
	std::vector<Incrementer*> incrementers;
	incrementers.push_back(factory->createIncrementerFromString(
			jsonAction["currentIncrementMode"].asString(),
			tryExtractingParametersFromJson(jsonAction["currentIncrementerParameters"])));
	incrementers.push_back(factory->createIncrementerFromString(
			jsonAction["pulseWidthIncrementMode"].asString(),
			tryExtractingParametersFromJson(jsonAction["pulseWidthIncrementerParameters"])));
	return incrementers;
}

void StimulationActionFactory::throwIfBadSetterActionGrammar(Json::Value& json) {
	if (!json.isMember("channel"))
		throw new json::errors::MissingParameterException("", "channel");
	if (!json.isMember("current"))
		throw new json::errors::MissingParameterException("", "current");
	if(!json.isMember("pulseWidth"))
		throw new json::errors::MissingParameterException("", "pulseWidth");
}

void StimulationActionFactory::throwIfBadTimeLimitedActionGrammar(Json::Value& action) {
	if (!action.isMember("delay"))
		throw new json::errors::MissingParameterException("", "delay");
	if (!action.isMember("channel"))
		throw new json::errors::MissingParameterException("", "channel");
	if(!action.isMember("duration"))
		throw new json::errors::MissingParameterException("", "duration");
	if(!action.isMember("currentIncrementMode"))
		throw new json::errors::MissingParameterException("", "currentIncrementMode");
	if(!action.isMember("pulseWidthIncrementMode"))
		throw new json::errors::MissingParameterException("", "pulseWidthIncrementMode");
	if(!action.isMember("currentIncrementMode"))
		throw new json::errors::MissingParameterException("", "currentDecrementMode");
	if(!action.isMember("pulseWidthDecrementMode"))
		throw new json::errors::MissingParameterException("", "pulseWidthDecrementMode");
	if(!action.isMember("pulseWidthIncrementerParameters"))
		throw new json::errors::MissingParameterException("", "pulseWidthIncrementerParameters");
	if(!action.isMember("currentIncrementerParameters"))
		throw new json::errors::MissingParameterException("", "currentIncrementerParameters");
	if(!action.isMember("currentDecrementerParameters"))
		throw new json::errors::MissingParameterException("", "currentDecrementerParameters");
	if(!action.isMember("pulseWidthDecrementerParameters"))
		throw new json::errors::MissingParameterException("", "pulseWidthDecrementerParameters");
}

void StimulationActionFactory::throwIfBadGrammar(Json::Value* action){
	if((*action)["actionType"].asString() == "limited"){
		throwIfBadTimeLimitedActionGrammar(*action);
	}
	else if((*action)["actionType"].asString() == "setter"){
		throwIfBadSetterActionGrammar(*action);
	}

}
