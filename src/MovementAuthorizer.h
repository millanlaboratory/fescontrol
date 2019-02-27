/*
 * MovementAuthorized.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "errors/JsonException.h"
#include "errors/AuthorizerException.h"



class MovementAuthorizer {
public:
	MovementAuthorizer();
	virtual ~MovementAuthorizer();
	virtual void init(std::string filename);
	virtual void init();
	virtual std::string getFileName(){return fileName;}
	virtual std::string getMovementFileNameFromEventId(int id);

	virtual void setFileName(std::string nFileName);

protected:
	Json::Value tryParsingJsonFile();
	void throwIfEmpty(Json::Value& obj);
	void throwIfBadGrammar(Json::Value obj);
	void checkForBadJsonFile(Json::Value obj);


protected:
	std::string fileName;
	std::vector<Json::Value> authorizedMovements;
};
