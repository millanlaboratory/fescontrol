#pragma once

#include "Incrementer.h"
#include <vector>
#include "errors/StimulationException.h"

class LinearIncrementer: public Incrementer {
public:
	LinearIncrementer(double minimumValue,double maximumValue, double duration);
	LinearIncrementer(std::vector<double> parameters);
	virtual ~LinearIncrementer(){}
	Incrementer* getDecrementer();
	double getIncrement(float dt, float currentValue);
	double getDecrement(float dt, float currentValue);

	double startingValue;
	double endingValue;
};
