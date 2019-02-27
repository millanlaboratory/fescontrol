/*
 * ConnectedApplication.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */
#pragma once

#include "Application.h"
#include "interfaces/ClLoopInstance.h"
#include "interfaces/ClTobiIdInstance.h"
#include "errors/LoopException.h"
#include "interfaces/CcCoreInstance.h"
#include "MovementAuthorizer.h"

#define CNBI_DEVBUS_FLEXION  14
#define EXIT_EVENT 404

class ConnectedApplication: public Application {
public:
	ConnectedApplication(bool verbose);
	virtual ~ConnectedApplication();
	virtual void init(CcCoreInstance*, ClTobiIdInstance*, ClLoopInstance*, FESStimulator*, FESJsonReader*, MovementAuthorizer*);
	ClTobiIdInstance* getTobiId(){return tobiId;}
	ClLoopInstance* getLoop(){return loop;}
	CcCoreInstance* getCore(){return core;}
	MovementAuthorizer* getAuthorizer(){return authorizer;}
	virtual void throwIfLoopDisconnected();
	virtual void handleNewCommands();
	virtual void start();

protected:
	virtual void runApplication();
	virtual bool isDone();
	void connectToCNBILoop();
	ClTobiIdInstance* tobiId;
	ClLoopInstance* loop;
	CcCoreInstance* core;
	MovementAuthorizer* authorizer;

private:
	std::string tryGettingMovementFileNameFromEventId();
};


