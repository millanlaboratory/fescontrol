#pragma once
#include "../../../src/StimulationAction.h"
#include <iostream>

class StimulationActionMock: public StimulationAction{
public:
	MOCK_METHOD0(stimulate, void());
	MOCK_METHOD5(init, void(Channel*, double, double, std::vector<Incrementer*>, std::vector<Incrementer*>));
	MOCK_METHOD1(update, void(double));
	MOCK_METHOD0(isStimulating, bool());
	MOCK_METHOD1(areSimultaneousActions, bool(StimulationAction*));
};
