/*
 * ClTobiIdInstance.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include "ClTobiId.hpp"


class ClTobiIdInstance{
public:
	ClTobiIdInstance(int mode = ClTobiId::SetOnly, float waitms = 3.00, std::string name = "/dev");
	ClTobiIdInstance(IDSerializerRapid* serializerI, IDMessage* messageI,
			int mode = ClTobiId::SetOnly, float waitms = 3.00);
	virtual ~ClTobiIdInstance();
	virtual bool Attach();
	virtual bool Detach(void);
	virtual bool IsAttached(void);
	virtual bool GetMessage();
	virtual bool GetMessage(IDSerializerRapid* serializer);
	virtual bool SetMessage(IDSerializerRapid* serializer,
			int blockidx = TCBlock::BlockIdxUnset, int* fixd = NULL);
	virtual IDevent getEvent();
	virtual int Count(void);
	virtual int Clear(void);
	virtual std::string getBusName();
private:
	ClTobiId* tobiId;
	IDMessage* messageI;
	IDSerializerRapid* serializerI;
	std::string busName;

};

