/*
 * CcCoreInstance.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#pragma once
#include <cnbicore/CcBasic.hpp>
#include <cnbicore/CcThreadSafe.hpp>

class CcCoreInstance {
public:
	CcCoreInstance();
	virtual ~CcCoreInstance();
	virtual void Release(void);
	virtual void Exit(int retcode);
	virtual unsigned int Refcount(void);
	virtual void Status(void);
	virtual void OpenLogger(std::string modulename,
			CcTermType termtype = CcCore::TerminalColors,
			CcLogLevel level = CcCore::LevelConfig);
	virtual void CloseLogger(void);
	virtual std::string GetDirectoryTmp(void);
	virtual std::string GetDirectoryCwd(void);
	virtual std::string GetDirectoryHome(void);
	virtual std::string GetUsername(void);
	virtual std::string GetModulename(void);
	virtual std::string GetEnvCnbiTkData(void);
	virtual std::string GetEnvCnbiTkMat(void);
	virtual std::string GetEnvTobiCoreMat(void);
	virtual void CatchSIGINT(void);
	virtual void CatchSIGQUIT(void);
	virtual void CatchSIGTERM(void);
	virtual void CatchSIGCHLD(void);

	virtual CcLogger& getLogger();
	virtual CcThreadSafe<bool>* receivedSIGAny();
	virtual CcThreadSafe<bool>* receivedSIGINT();
	virtual CcThreadSafe<bool>* receivedSIGQUIT();
	virtual CcThreadSafe<bool>* receivedSIGTERM();
	virtual CcThreadSafe<bool>* receivedSIGCHLD();

public:
	static const CcTermType TerminalDisabled = 0;
	static const CcTermType TerminalEnabled = 1;
	static const CcTermType TerminalColors = 2;
	static const CcLogLevel LevelDebug = 10;
	static const CcLogLevel LevelConfig = 20;
	static const CcLogLevel LevelInfo = 30;
	static const CcLogLevel LevelException = 40;
	static const CcLogLevel LevelWarning = 50;
	static const CcLogLevel LevelError = 60;
	static const CcLogLevel LevelFatal = 70;
};

