/*
 * MovementAuthorized.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cnbiadministrator
 */

#include "MovementAuthorizer.h"

MovementAuthorizer::MovementAuthorizer() {
	// TODO Auto-generated constructor stub

}

MovementAuthorizer::~MovementAuthorizer() {
	// TODO Auto-generated destructor stub
}

void MovementAuthorizer::init(std::string filename){
	setFileName(filename);
	init();
}

void MovementAuthorizer::init(){
	Json::Value obj = tryParsingJsonFile();
	checkForBadJsonFile(obj);
	for (unsigned int i(0); i < obj["Movements"].size(); ++i){
		authorizedMovements.push_back(obj["Movements"][i]);
	}
}

Json::Value MovementAuthorizer::tryParsingJsonFile() {
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open()) {
		throw new json::errors::JsonException(fileName);
	}
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	return obj;
}

void MovementAuthorizer::throwIfEmpty(Json::Value& obj) {
	if (!obj.isMember("Movements")) {
		for(auto& name : obj.getMemberNames()){
			std::cerr << name << std::endl;
		}
		throw new json::errors::EmptyException(fileName);
	}
}

void MovementAuthorizer::throwIfBadGrammar(Json::Value obj) {
	if (obj["Movements"].isArray() && obj["Movements"].size() != 0) {
		for(unsigned int i(0); i < obj["Movements"].size(); ++i){
			Json::Value movement = obj["Movements"][i];
			if (!movement.isMember("Name") ||
					!movement.isMember("EventId") ||
					!movement.isMember("MovementFile") ) {
				throw new json::errors::BadGrammarException(fileName);
			}
		}
	}
}

void MovementAuthorizer::checkForBadJsonFile(Json::Value obj) {
	throwIfEmpty(obj);
	throwIfBadGrammar(obj);
}

std::string MovementAuthorizer::getMovementFileNameFromEventId(int id){
	for (unsigned int i(0); i < authorizedMovements.size(); ++i){
		if(authorizedMovements[i]["EventId"].asInt() == id){
			return authorizedMovements[i]["MovementFile"].asString();
		}
	}
	throw new auth::errors::UnauthorizedMovementIdException(fileName);
}

void MovementAuthorizer::setFileName(std::string nFileName){
	fileName = nFileName;
}
