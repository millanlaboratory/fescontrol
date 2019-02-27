/*
 * ConnectedApplicationTestCase.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#include "gmock/gmock.h"
#include "../../src/ConnectedApplication.h"
#include "../../src/MovementAuthorizer.h"
#include "mocks/StimulationActionMock.h"
#include "ApplicationTestCase.h"


class CcCoreMock : public CcCoreInstance{
public:
	MOCK_METHOD0(receivedSIGAny, CcThreadSafe<bool>*());
	MOCK_METHOD3(OpenLogger, void(std::string, CcTermType, CcLogLevel));
};

class MovementAuthorizerMock : public MovementAuthorizer{
public:
	MOCK_METHOD1(init, void(std::string));
	MOCK_METHOD0(init, void());
	MOCK_METHOD1(getMovementFileNameFromEventId, std::string(int));
};


class ConnectedApplicationTestCase: public ApplicationTestCase{
public:
	ConnectedApplicationTestCase(){

	}
	virtual ~ConnectedApplicationTestCase(){
	}
	virtual void initApp(){
		app = new ConnectedApplication(true);
	}

	void init(){
		ApplicationTestCase::init();
		tobiIdMock = new ClTobiIdMock();
		loopMock = new ClLoopMock();
		coreMock = new CcCoreMock();
		authorizerMock = new MovementAuthorizerMock();
	}

	void expectSuccessfulLoopInitialization(){
		EXPECT_CALL(*coreMock, OpenLogger(::testing::_,::testing::_,::testing::_)).Times(1);
		EXPECT_CALL(*loopMock, Configure(::testing::_,::testing::_)).Times(1);
		EXPECT_CALL(*loopMock, Connect()).Times(1).WillOnce(::testing::Return(true));
		EXPECT_CALL(*tobiIdMock, Attach()).Times(1).WillOnce(::testing::Return(true));
		EXPECT_CALL(*authorizerMock, init()).Times(1);
	}

	void expectSuccessfulLoopDestruction(){
		EXPECT_CALL(*tobiIdMock, IsAttached()).Times(1).WillRepeatedly(::testing::Return(true));
	}

	ClTobiIdMock* tobiIdMock;
	ClLoopMock* loopMock;
	CcCoreMock* coreMock;
	MovementAuthorizerMock* authorizerMock;
};

TEST_F(ConnectedApplicationTestCase, createApplicationSuccess){
	init();
	expectSuccessfulStimReaderInitialization();
	expectSuccessfulLoopInitialization();
	((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock);
	ASSERT_EQ(app->getStimulator(), stimMock);
	ASSERT_EQ(app->getJsonReader(), readerMock);
	ASSERT_EQ(((ConnectedApplication*)app)->getAuthorizer(), authorizerMock);
	ASSERT_EQ(((ConnectedApplication*)app)->getCore(), coreMock);
	expectSuccessfulLoopDestruction();
}

TEST_F(ConnectedApplicationTestCase, StartApplicationSuccess){
	init();
	expectSuccessfulStimReaderInitialization();
	expectSuccessfulLoopInitialization();
	((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock);

	EXPECT_CALL(*stimMock, start()).Times(1);
	EXPECT_CALL(*loopMock, IsConnected()).Times(::testing::AnyNumber()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, IsAttached()).Times(::testing::AnyNumber()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, GetMessage()).Times(::testing::AnyNumber()).WillRepeatedly(::testing::Return(false));
	CcThreadSafe<bool>* dummyTrueThread = new CcThreadSafe<bool>(true);
		CcThreadSafe<bool>* dummyFalseThread = new CcThreadSafe<bool>(false);
	EXPECT_CALL(*coreMock, receivedSIGAny()).Times(2).WillOnce(::testing::Return(dummyFalseThread)).WillOnce(
			::testing::Return(dummyTrueThread));
	((ConnectedApplication*)app)->start();

}

TEST_F(ConnectedApplicationTestCase, ReceivingCommandSuccess){
	init();
	expectSuccessfulStimReaderInitialization();
	expectSuccessfulLoopInitialization();
	((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock);
	StimulationActionMock* stimAction = new StimulationActionMock();

	EXPECT_CALL(*readerMock, getSequenceFromJsonFile(::testing::_)).Times(1).WillOnce(
			::testing::Return(std::vector<StimulationAction*>{stimAction}));
	EXPECT_CALL(*stimMock, addStimulationAction(::testing::_)).Times(1);
	EXPECT_CALL(*stimMock, start()).Times(2);
	EXPECT_CALL(*loopMock, IsConnected()).Times(::testing::AnyNumber()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, IsAttached()).Times(::testing::AnyNumber()).WillRepeatedly(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, GetMessage()).Times(2).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));
	EXPECT_CALL(*tobiIdMock, getEvent()).Times(2);
	EXPECT_CALL(*stimMock, removeAllActions()).Times(1);
	EXPECT_CALL(*authorizerMock, getMovementFileNameFromEventId(::testing::_)).Times(1).WillOnce(::testing::Return("file.json"));
	CcThreadSafe<bool>* dummyTrueThread = new CcThreadSafe<bool>(true);
	CcThreadSafe<bool>* dummyFalseThread = new CcThreadSafe<bool>(false);
	EXPECT_CALL(*coreMock, receivedSIGAny()).Times(2).WillOnce(::testing::Return(dummyFalseThread)).WillOnce(
			::testing::Return(dummyTrueThread));
	((ConnectedApplication*)app)->start();
	expectSuccessfulLoopDestruction();
	delete stimAction;
}

TEST_F(ConnectedApplicationTestCase, ImpossibleToConnectToLoopShouldThrow){
	init();
	expectSuccessfulStimReaderInitialization();
	EXPECT_CALL(*coreMock, OpenLogger(::testing::_,::testing::_,::testing::_)).Times(1);
	EXPECT_CALL(*loopMock, Configure(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(true));
	EXPECT_CALL(*loopMock, Connect()).Times(1).WillOnce(::testing::Return(false));
	EXPECT_CALL(*authorizerMock, init()).Times(1);
	EXPECT_THROW(((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock),
			loop::errors::ImpossibleToConnectException*);
	expectSuccessfulLoopDestruction();
}

TEST_F(ConnectedApplicationTestCase, ImpossibleToAttachIdShouldThrow){
	init();
	expectSuccessfulStimReaderInitialization();
	EXPECT_CALL(*coreMock, OpenLogger(::testing::_,::testing::_,::testing::_)).Times(1);
	EXPECT_CALL(*loopMock, Configure(::testing::_,::testing::_)).Times(1).WillOnce(::testing::Return(true));
	EXPECT_CALL(*loopMock, Connect()).Times(1).WillOnce(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, Attach()).Times(1).WillOnce(::testing::Return(false));
	EXPECT_CALL(*authorizerMock, init()).Times(1);
	EXPECT_THROW(((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock),
			loop::errors::ImpossibleToAttachIdException*);
	expectSuccessfulLoopDestruction();
}

TEST_F(ConnectedApplicationTestCase, IdNotAttachedAnymoreShouldThrow){
	init();
	expectSuccessfulStimReaderInitialization();
	expectSuccessfulLoopInitialization();
	((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock);
	EXPECT_CALL(*stimMock, start()).Times(1);
	EXPECT_CALL(*loopMock, IsConnected()).Times(1).WillOnce(::testing::Return(true));
	EXPECT_CALL(*tobiIdMock, IsAttached()).Times(1).WillOnce(::testing::Return(false));
	CcThreadSafe<bool>* dummyFalseThread = new CcThreadSafe<bool>(false);
	EXPECT_CALL(*coreMock, receivedSIGAny()).Times(1).WillOnce(::testing::Return(dummyFalseThread));
	EXPECT_THROW(((ConnectedApplication*)app)->start(), loop::errors::LostIdConnectionException*);
	expectSuccessfulLoopDestruction();
}

TEST_F(ConnectedApplicationTestCase, LoopNoConnectedAnymoreShouldThrow){
	init();
	expectSuccessfulStimReaderInitialization();
	expectSuccessfulLoopInitialization();
	((ConnectedApplication*)app)->init(coreMock, tobiIdMock, loopMock, stimMock, readerMock, authorizerMock);
	EXPECT_CALL(*stimMock, start()).Times(1);
	CcThreadSafe<bool>* dummyFalseThread = new CcThreadSafe<bool>(false);
	EXPECT_CALL(*coreMock, receivedSIGAny()).Times(1).WillOnce(::testing::Return(dummyFalseThread));
	EXPECT_CALL(*loopMock, IsConnected()).Times(1).WillOnce(::testing::Return(false));
	EXPECT_THROW(((ConnectedApplication*)app)->start(), loop::errors::LostLoopConnectionException*);
	expectSuccessfulLoopDestruction();
}


