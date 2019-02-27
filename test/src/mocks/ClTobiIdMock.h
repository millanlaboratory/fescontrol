/*
 * ClTobiIdMock.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "../../../src/interfaces/ClTobiIdInstance.h"
#include "gmock/gmock.h"

class ClTobiIdMock: public ClTobiIdInstance{
public:
	MOCK_METHOD0(getEvent, IDevent());
	MOCK_METHOD0(GetMessage, bool());
	MOCK_METHOD1(GetMessage, bool(IDSerializerRapid*));
	MOCK_METHOD0(Attach, bool());
	MOCK_METHOD0(IsAttached, bool());
};
