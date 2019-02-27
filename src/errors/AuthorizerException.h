/*
 * AuthorizerException.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cnbiadministrator
 */

#pragma once

#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception
#include <string>     		// std::string, std::to_string


namespace auth{
namespace errors{

class UnauthorizedMovementIdException : public std::exception{
public:
	UnauthorizedMovementIdException(std::string filename): file(filename){

	}
	virtual const char* what() const throw()
	  {
	    return ("Unknown movement id. Check " + file + " to know which movement is allowed").c_str();
	  }
	std::string file;
};
}
}
