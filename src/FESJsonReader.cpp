#include "FESJsonReader.h"
#include "IncrementerFactory.h"
#include "TimeLimitedAction.h"

FESJsonReader::~FESJsonReader(){
	delete stimFactory;
}

void FESJsonReader::init(FESStimulator* nStimulator,StimulationActionFactory* factory){
	stimulator = nStimulator;
	stimFactory = factory;
	stimFactory->init(stimulator, new IncrementerFactory());
}



std::vector<StimulationAction*> FESJsonReader::getSequenceFromJsonFile(std::string file) {
	fileName = file;
	Json::Value obj = tryParsingJsonFile(file);
	checkForBadJsonFile(obj);
	std::vector<StimulationAction*> sequence;
	for(unsigned int actionIndex(0); actionIndex < obj["sequence"].size(); ++actionIndex){
		StimulationAction* action = tryCreatingStimulationAction(obj,actionIndex);
		throwIfActionsAreSimultaneous(sequence, action);
		sequence.push_back(action);
	}
	stimulator->setFrequency(obj["frequency"].asInt());
	return sequence;
}

void FESJsonReader::throwIfActionsAreSimultaneous(
		const std::vector<StimulationAction*>& sequence,
		StimulationAction* action) {
	for (unsigned int index(0); index < sequence.size(); ++index) {
		if (action->areSimultaneousActions(sequence[index])) {
			throw new json::errors::SimultaneousStimulationException(fileName);
		}
	}
}

StimulationAction* FESJsonReader::tryCreatingStimulationAction(
		Json::Value& obj, unsigned int actionIndex) {
	StimulationAction* action(nullptr);
	try {
		action = stimFactory->createStimulationActionFromJson(&(obj["sequence"][actionIndex]));
	} catch (std::exception* e) {
		std::cerr << e->what() << std::endl;
		throw new json::errors::BadGrammarException(fileName);
	}
	return action;
}

Json::Value FESJsonReader::tryParsingJsonFile(std::string file) {
	std::ifstream ifs(file.c_str());
	if (!ifs.is_open()) {
		throw new json::errors::JsonException(fileName);
	}
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	return obj;
}

void FESJsonReader::throwIfEmpty(Json::Value& obj) {
	if (!obj.isMember("sequence")) {
		throw new json::errors::EmptyException(fileName);
	}
}

void FESJsonReader::throwIfBadActionGrammar(Json::Value& action) {
	if (!action.isMember("delay") || !action.isMember("channel") || !action.isMember("duration")
			|| !action.isMember("currentIncrementMode") || !action.isMember("pulseWidthIncrementMode")
			|| !action.isMember("currentIncrementMode") || !action.isMember("pulseWidthDecrementMode")
			|| !action.isMember("currentIncrementerParameters") || !action.isMember("pulseWidthIncrementerParameters")
			|| !action.isMember("currentIncrementerParameters")
			|| !action.isMember("pulseWidthDecrementerParameters")) {
		throw new json::errors::BadGrammarException(fileName);
	}
}

void FESJsonReader::throwIfBadGrammar(Json::Value obj) {
	if(!obj.isMember("frequency")){
		throw new json::errors::BadGrammarException(fileName);
	}
	if (obj["sequence"].isArray() && obj["sequence"].size() != 0) {
		for(unsigned int i(0); i < obj["sequence"].size(); ++i){
			stimFactory->throwIfBadGrammar(&(obj["sequence"][i]));
		}
	}
}

void FESJsonReader::checkForBadJsonFile(Json::Value obj) {
	throwIfEmpty(obj);
	throwIfBadGrammar(obj);
}
