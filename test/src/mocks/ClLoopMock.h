/*
 * ClLoopMock.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "../../../src/interfaces/ClLoopInstance.h"
#include "gmock/gmock.h"


class ClLoopMock: public ClLoopInstance{
public:
	MOCK_METHOD0(Connect, bool(void));
	MOCK_METHOD1(Connect, bool(CcAddress));
	MOCK_METHOD1(Connect, bool(CCfgConfig* ));
	MOCK_METHOD0(IsConnected, bool());
	MOCK_METHOD2(Configure, bool(CcAddress, bool));
};
