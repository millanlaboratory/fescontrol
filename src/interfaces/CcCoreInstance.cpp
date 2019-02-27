/*
 * CcCoreInstance.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#include "CcCoreInstance.h"

CcCoreInstance::CcCoreInstance() {
	// TODO Auto-generated constructor stub

}

CcCoreInstance::~CcCoreInstance() {
	// TODO Auto-generated destructor stub
}


void CcCoreInstance::Release(void){
	CcCore::Release();
}
void CcCoreInstance::Exit(int retcode){
	CcCore::Exit(retcode);
}
unsigned int CcCoreInstance::Refcount(void){
	return CcCore::Refcount();
}
void CcCoreInstance::Status(void){
	CcCore::Status();
}
void CcCoreInstance::OpenLogger(std::string modulename, CcTermType termtype, CcLogLevel level){
	CcCore::OpenLogger(modulename, termtype, level);
}
void CcCoreInstance::CloseLogger(void){
	CcCore::CloseLogger();
}
std::string CcCoreInstance::GetDirectoryTmp(void){
	return CcCore::GetDirectoryTmp();
}
std::string CcCoreInstance::GetDirectoryCwd(void){
	return CcCore::GetDirectoryCwd();
}
std::string CcCoreInstance::GetDirectoryHome(void){
	return CcCore::GetDirectoryHome();
}

std::string CcCoreInstance::GetUsername(void){
	return CcCore::GetUsername();
}

std::string CcCoreInstance::GetModulename(void){
	return CcCore::GetModulename();
}
std::string CcCoreInstance::GetEnvCnbiTkData(void){
	return CcCore::GetEnvCnbiTkData();
}
std::string CcCoreInstance::GetEnvCnbiTkMat(void){
	return CcCore::GetEnvCnbiTkMat();
}
std::string CcCoreInstance::GetEnvTobiCoreMat(void){
	return CcCore::GetEnvTobiCoreMat();
}
void CcCoreInstance::CatchSIGINT(void){
	CcCore::CatchSIGINT();
}
void CcCoreInstance::CatchSIGQUIT(void){
	CcCore::CatchSIGQUIT();
}

void CcCoreInstance::CatchSIGTERM(void){
	CcCore::CatchSIGTERM();
}
void CcCoreInstance::CatchSIGCHLD(void){
	CcCore::CatchSIGCHLD();
}

CcLogger& CcCoreInstance::getLogger(){
	return CcCore::logger;
}
CcThreadSafe<bool>* CcCoreInstance::receivedSIGAny(){
	return &CcCore::receivedSIGAny;
}
CcThreadSafe<bool>* CcCoreInstance::receivedSIGINT(){
	return &CcCore::receivedSIGINT;
}
CcThreadSafe<bool>* CcCoreInstance::receivedSIGQUIT(){
	return &CcCore::receivedSIGQUIT;
}
CcThreadSafe<bool>* CcCoreInstance::receivedSIGTERM(){
	return &CcCore::receivedSIGTERM;
}
CcThreadSafe<bool>* CcCoreInstance::receivedSIGCHLD(){
	return &CcCore::receivedSIGCHLD;
}

