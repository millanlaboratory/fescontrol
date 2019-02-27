/*
 * FESStimulatorMock.h
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */

#pragma once

#include "../../../src/FESStimulator.h"
#include "gmock/gmock.h"
#include "SerialPortMock.h"

class FESStimulatorMock: public FESStimulator{
public:
	FESStimulatorMock():FESStimulator(){}
	virtual ~FESStimulatorMock(){}
	MOCK_METHOD1(getChannelByChannelNumber, Channel*(int));
	MOCK_METHOD1(addChannel, void(Channel*));
	MOCK_METHOD1(addStimulationAction, void(StimulationAction*));
	MOCK_METHOD0(removeAllActions, void());
	MOCK_METHOD0(resetChannels, void());
	MOCK_METHOD0(start, void());
	MOCK_METHOD1(update, void(float));
	MOCK_METHOD0(areActionsComplete, bool());
	MOCK_METHOD2(init, void(SerialPort*, sp_tty*));
};
