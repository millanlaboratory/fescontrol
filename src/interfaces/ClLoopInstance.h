/*
 * ClLoopInstance.h
 *
 *  Created on: Oct 13, 2017
 *      Author: cnbiadministrator
 */

#pragma once

#include "ClLoop.hpp"

class ClLoopInstance{
public:
	ClLoopInstance();
	ClLoop* Instance(void);
	virtual ~ClLoopInstance(){}
	virtual void Release(void);
	virtual unsigned int Refcount(void);
	virtual bool Connect(void);
	virtual bool Connect(CcAddress nameserver);
	virtual bool Connect(CCfgConfig* configuration);
	virtual void Disconnect(void);
	virtual bool IsConnected(void);
	virtual bool Configure(CcAddress nameserver = "", bool asserver = false);
};

