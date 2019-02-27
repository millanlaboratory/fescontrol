#pragma once

#include <string>
#include "errors/JsonException.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include "StimulationAction.h"
#include "LinearIncrementer.h"
#include "FESStimulator.h"
#include "IncrementerFactory.h"
#include "StimulationActionFactory.h"

class FESJsonReader{
public:
	virtual ~FESJsonReader();
	virtual void init(FESStimulator*,StimulationActionFactory*);
	virtual std::vector<StimulationAction*> getSequenceFromJsonFile(std::string file);
	virtual FESStimulator* getStimulator(){return stimulator;}
	virtual StimulationActionFactory* getStimulationActionFactory(){return stimFactory;}

private:
	Json::Value tryParsingJsonFile(std::string file);

	void throwIfEmpty(Json::Value& obj);

	void throwIfBadGrammar(Json::Value obj);

	void checkForBadJsonFile(Json::Value obj);
	std::vector<double> tryExtractingParametersFromJson(Json::Value& obj);
	StimulationAction* createStimActionFromJsonAction(
			FESStimulator* stimulator, Json::Value& jsonAction,IncrementerFactory& factory);
	std::vector<Incrementer*> generateIncrementers(Json::Value& jsonAction,	IncrementerFactory& factory);
	std::vector<Incrementer*> generateDecrementers(Json::Value& jsonAction,	IncrementerFactory& factory);
	void throwIfBadActionGrammar(Json::Value& action);
	void throwIfActionsAreSimultaneous(
			const std::vector<StimulationAction*>& sequence,
			StimulationAction* action);
	StimulationAction* tryCreatingStimulationAction(Json::Value& obj, unsigned int actionIndex);

	std::string fileName;
	FESStimulator* stimulator;
	StimulationActionFactory* stimFactory;
};

