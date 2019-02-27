/*
 * IncrementerFactory.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */

#include "IncrementerFactory.h"
#include "LinearIncrementer.h"

IncrementerFactory::IncrementerFactory() {

}

IncrementerFactory::~IncrementerFactory() {

}

Incrementer* IncrementerFactory::createIncrementerFromString(std::string incrementerType, std::vector<double> parameters){
	if(incrementerType == "linear"){
		return new LinearIncrementer(parameters);
	}
	throw stim::errors::IncrementerException(incrementerType);
}
