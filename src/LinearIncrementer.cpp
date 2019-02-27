
#include "LinearIncrementer.h"

LinearIncrementer::LinearIncrementer(double minimumValue, double maximumValue, double duration):
Incrementer(duration), startingValue(minimumValue), endingValue(maximumValue)
{
}

LinearIncrementer::LinearIncrementer(std::vector<double> parameters){
	if(parameters.size() != 3){
		throw stim::errors::WrongParametersException(3,parameters.size());
	}
	startingValue = parameters[0];
	endingValue = parameters[1];
	duration = parameters[2];
}

double LinearIncrementer::getIncrement(float dt, float currentValue){
	called = true;
	if(duration == 0){
		return currentValue < endingValue ? (endingValue - startingValue) : 0;
	}
	double increment = (endingValue - startingValue) / duration * dt;
	increment = currentValue + increment < endingValue ? increment : (endingValue - currentValue) - 0.00001;
	return currentValue < endingValue ? increment : 0;
}


double LinearIncrementer::getDecrement(float dt, float currentValue){
	called = true;
	if(duration == 0){
		return currentValue > startingValue ? (startingValue - endingValue) : 0;
	}
	double decrement = (startingValue - endingValue) / duration * dt;
	decrement = currentValue + decrement > startingValue ? decrement : (startingValue - currentValue) + 0.00001;
	return currentValue > startingValue ? decrement : 0;
}

Incrementer* LinearIncrementer::getDecrementer(){
	return new LinearIncrementer(endingValue, startingValue, duration);
}
