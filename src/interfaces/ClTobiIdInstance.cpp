/*
 * ClTobiIdInstance.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#include "ClTobiIdInstance.h"

ClTobiIdInstance::ClTobiIdInstance(int mode, float waitms, std::string name): tobiId(new ClTobiId(mode, waitms)),
messageI(new IDMessage()),
serializerI(new IDSerializerRapid(messageI)),
busName(name){
}

ClTobiIdInstance::ClTobiIdInstance(IDSerializerRapid* nSerializerI, IDMessage* nMessageI, int mode, float waitms):
		tobiId(new ClTobiId(mode, waitms)),
		messageI(nMessageI),
		serializerI(nSerializerI){
}

ClTobiIdInstance::~ClTobiIdInstance() {
}

bool ClTobiIdInstance::Attach(){
	return tobiId->Attach(busName);
}

bool ClTobiIdInstance::Detach(void){
	return tobiId->Detach();
}
bool ClTobiIdInstance::IsAttached(void){
	return tobiId->IsAttached();
}

bool ClTobiIdInstance::GetMessage(){
	return GetMessage(serializerI);
}

bool ClTobiIdInstance::GetMessage(IDSerializerRapid* serializer){
	return tobiId->GetMessage(serializer);
}

bool ClTobiIdInstance::SetMessage(IDSerializerRapid* serializer,
		int blockidx, int* fixd){
	return tobiId->SetMessage(serializer, blockidx, fixd);
}

int ClTobiIdInstance::Count(void){
	return tobiId->Count();
}

int ClTobiIdInstance::Clear(void){
	return tobiId->Clear();
}

IDevent ClTobiIdInstance::getEvent(){
	return messageI->GetEvent();
}

std::string ClTobiIdInstance::getBusName(){
	return busName;
}

