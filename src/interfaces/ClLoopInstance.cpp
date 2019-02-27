/*
 * ClLoopInstance.cpp
 *
 *  Created on: Oct 13, 2017
 *      Author: cnbiadministrator
 */

#include "ClLoopInstance.h"

ClLoopInstance::ClLoopInstance(){
	// TODO Auto-generated constructor stub

}

ClLoop* ClLoopInstance::Instance(void){
	return ClLoop::Instance();
}

void ClLoopInstance::Release(void){
	ClLoop::Release();
}

unsigned int ClLoopInstance::Refcount(void){
	return ClLoop::Refcount();
}

bool ClLoopInstance::Connect(void){
	return ClLoop::Connect();
}

bool ClLoopInstance::Connect(CcAddress nameserver){
	return ClLoop::Connect(nameserver);
}

bool ClLoopInstance::Connect(CCfgConfig* configuration){
	return ClLoop::Connect(configuration);
}

void ClLoopInstance::Disconnect(void){
	ClLoop::Disconnect();
}

bool ClLoopInstance::IsConnected(void){
	return ClLoop::IsConnected();
}

bool ClLoopInstance::Configure(CcAddress nameserver, bool asserver){
	return ClLoop::Configure(nameserver,asserver);
}
