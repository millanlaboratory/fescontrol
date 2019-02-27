/*
 * FESJsonReaderMock.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */
#pragma once

#include "../../../src/FESJsonReader.h"
#include "gmock/gmock.h"

class FESJsonReaderMock: public FESJsonReader{
public:
	MOCK_METHOD2(init, void(FESStimulator*, StimulationActionFactory*));
	MOCK_METHOD1(getSequenceFromJsonFile, std::vector<StimulationAction*>(std::string));
};
