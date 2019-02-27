/*
 * ApplicationTestCase.h
 *
 *  Created on: Dec 20, 2017
 *      Author: cnbi
 */

#pragma once

#include "../../src/Application.h"
#include "gmock/gmock.h"
#include "mocks/FESStimulatorMock.h"
#include "mocks/FESJsonReaderMock.h"
#include "mocks/ClTobiIdMock.h"
#include "mocks/ClLoopMock.h"

class ApplicationTestCase: public testing::Test {
public:
	ApplicationTestCase() {
	}

	~ApplicationTestCase() {
		delete app;
	}

	virtual void initApp() {
		app = new Application(false);
	}

	virtual void init() {
		file = "resources/file.json";
		initApp();
		stimMock = new FESStimulatorMock();
		readerMock = new FESJsonReaderMock();
	}

	void expectSuccessfulStimReaderInitialization(){
		EXPECT_CALL(*stimMock, addChannel(::testing::_)).Times(8);
		EXPECT_CALL(*stimMock, init(::testing::_,::testing::_)).Times(1);
		EXPECT_CALL(*readerMock, init(stimMock,::testing::_)).Times(1);
	}


	std::string file;
	Application* app;
	FESStimulatorMock* stimMock;
	FESJsonReaderMock* readerMock;
};
