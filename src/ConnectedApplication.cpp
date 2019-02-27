/*
 * ConnectedApplication.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#include "ConnectedApplication.h"

ConnectedApplication::ConnectedApplication(bool verbose):
Application(verbose){

}

ConnectedApplication::~ConnectedApplication() {
	CcLogInfo("Detach event receiver ");
	if(tobiId!= nullptr){
		if(tobiId->IsAttached()){
			tobiId->Detach();
		}
	}

	CcLogInfo("Delete loop");
	delete loop;
	CcLogInfo("Delete core");
	delete core;
	CcLogInfo("Delete authorizer");
	delete authorizer;
	CcLogInfo("Delete event receiver");
	delete tobiId;
}

void ConnectedApplication::init(
		CcCoreInstance* nCore,
		ClTobiIdInstance* nTobiId,
		ClLoopInstance* nLoop,
		FESStimulator* nStim,
		FESJsonReader* nRead,
		MovementAuthorizer* nAuthorizer){
	Application::init(nStim, nRead);
	tobiId = nTobiId;
	loop = nLoop;
	core = nCore;
	authorizer = nAuthorizer;
	authorizer->init();
	CcLogInfo("Authorizer initiated with " + authorizer->getFileName());
	connectToCNBILoop();
}

void ConnectedApplication::runApplication() {
	previousEpoch = std::chrono::system_clock::now();
	while (!isDone()) {
		throwIfLoopDisconnected();
		handleNewCommands();
		updateStimulator();
	}
}

void ConnectedApplication::connectToCNBILoop() {
	core->OpenLogger("fesctrl");
	core->CatchSIGTERM();
	loop->Configure();
	if (loop->Connect() == false) {
		throw new loop::errors::ImpossibleToConnectException();
	}
	if (tobiId->Attach() == false) {
		throw new loop::errors::ImpossibleToAttachIdException();
	}
	if(verbose)
		CcLogInfo("Event Receiver ID attached to loop on " + tobiId->getBusName());
}

void ConnectedApplication::throwIfLoopDisconnected() {
	if (loop->IsConnected() == false) {
		throw new loop::errors::LostLoopConnectionException();
	}
	if (tobiId->IsAttached() == false) {
		throw new loop::errors::LostIdConnectionException();
	}
}

bool ConnectedApplication::isDone(){
	if (core->receivedSIGINT()->Get() || core->receivedSIGAny()->Get() || core->receivedSIGTERM()->Get()) {
		if(verbose)
			CcLogWarning("Application exiting");
		return true;
	}
	return false;
}

std::string ConnectedApplication::tryGettingMovementFileNameFromEventId() {
	try {
		return authorizer->getMovementFileNameFromEventId(tobiId->getEvent());
	} catch (auth::errors::UnauthorizedMovementIdException* e) {
	} catch (std::exception* e) {
		throw e;
	}
	return "";
}

void ConnectedApplication::handleNewCommands() {
	while (tobiId->GetMessage() == true) {
		if(verbose)
			CcLogInfo("Got message");
		if(tobiId->getEvent() == EXIT_EVENT){
			if(verbose)
				CcLogInfo("Got exiting message");
			core->receivedSIGTERM()->Set(true);
		}
		std::string movementFile = tryGettingMovementFileNameFromEventId();
		if(movementFile != ""){
			if(verbose)
				CcLogInfo("Received movement event");
				CcLogInfo(movementFile);
			std::vector<StimulationAction*> actions = reader->getSequenceFromJsonFile(movementFile);
			stimulator->removeAllActions();
			for(unsigned int actionIndex(0); actionIndex < actions.size(); ++actionIndex){
				stimulator->addStimulationAction(actions[actionIndex]);
			}
			stimulator->start();
		}
	}
}

void ConnectedApplication::start(){
	if(verbose)
		CcLogInfo("Initializing stimulator");
	stimulator->start();
	if(verbose)
		CcLogInfo("Running stimulator");
	runApplication();
}

