/*
 * IncrementerMock.h
 *
 *  Created on: Dec 19, 2017
 *      Author: cnbi
 */

#pragma once
#include "../../../src/Incrementer.h"


class IncrementerMock: public Incrementer{
public:
	MOCK_METHOD2(getIncrement, double(float, float));
	MOCK_METHOD2(getDecrement, double(float, float));
	MOCK_METHOD0(calledOnce, bool());
	MOCK_METHOD0(getDuration, double());
	MOCK_METHOD0(getDecrementer, Incrementer*());
};
