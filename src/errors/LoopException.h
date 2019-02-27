/*
 * LoopException.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cnbiadministrator
 */

#pragma once

#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception

namespace loop{
namespace errors{

class ImpossibleToConnectException : public std::exception{
public:
	virtual const char* what() const throw()
	{
		return "Impossible to connect to Loop";
	}
};

class ImpossibleToAttachIdException : public std::exception{
public:
	virtual const char* what() const throw()
	{
		return "Impossible to attach tobiId to /dev";
	}
};

class LostIdConnectionException : public std::exception{
public:
	virtual const char* what() const throw()
	{
		return "ID connection down";
	}
};

class LostLoopConnectionException : public std::exception{
public:
	virtual const char* what() const throw()
	{
		return "Loop connection down";
	}
};

}
}
