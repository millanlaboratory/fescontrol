/*
 * ApplicationTest.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */
#include "ApplicationTestCase.h"

TEST_F(ApplicationTestCase, createApplicationSuccess){
	init();
	expectSuccessfulStimReaderInitialization();
	app->init(stimMock, readerMock);
	ASSERT_EQ(app->getStimulator(), stimMock);
	ASSERT_EQ(app->getJsonReader(), readerMock);
}

TEST_F(ApplicationTestCase, startApplicationSuccess){
	init();
	expectSuccessfulStimReaderInitialization();
	app->init(stimMock, readerMock);

	EXPECT_CALL(*readerMock, getSequenceFromJsonFile(::testing::_)).WillOnce(::testing::Return(std::vector<StimulationAction*>{nullptr}));
	EXPECT_CALL(*stimMock, addStimulationAction(::testing::_)).Times(1);
	EXPECT_CALL(*stimMock, start()).Times(1);
	EXPECT_CALL(*stimMock, areActionsComplete()).Times(2).WillOnce(::testing::Return(false)).WillOnce(::testing::Return(true));
	EXPECT_CALL(*stimMock, update(::testing::_)).Times(1);
	app->start(file);
}




