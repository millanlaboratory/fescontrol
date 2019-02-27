/*
 * IncrementerFactory.h
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "Incrementer.h"
#include <iostream>
#include <vector>

class IncrementerFactory {
public:
	IncrementerFactory();
	virtual ~IncrementerFactory();
	virtual Incrementer* createIncrementerFromString(std::string incrementerType, std::vector<double> parameters);
};
