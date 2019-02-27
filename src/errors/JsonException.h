#pragma once
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception

namespace json{
namespace errors{

class JsonException : public std::exception{
public:
	JsonException(std::string fileName = ""): file(fileName){}
	virtual const char* what() const throw()
	  {
		std::cerr << "Exception with json reader. Could not find: " + file << std::endl;
	    return "";
	  }
	std::string file;
};

class EmptyException : public JsonException{
public:
	EmptyException(std::string fileName): JsonException(fileName){}
	virtual const char* what() const throw()
	  {
		std::string error = "Empty file: " + file;
		std::cerr << error << std::endl;
	    return "";
	  }
};

class BadGrammarException : public JsonException{
public:
	BadGrammarException(std::string fileName): JsonException(fileName){}
	virtual const char* what() const throw()
	  {
		std::cerr <<  ("Bad grammar for json file: " + file) << std::endl;
	    return "";
	  }
};

class MissingParameterException : public JsonException{
public:
	MissingParameterException(std::string fileName, std::string parameter): JsonException(fileName){}
	virtual const char* what() const throw()
	  {
		std::cerr << "Missing parameter " << parameter << " in json file: " << file << std::endl;
	    return "";
	  }
	std::string parameter;
};

class SimultaneousStimulationException : public JsonException{
public:
	SimultaneousStimulationException(std::string fileName): JsonException(fileName){}
	virtual const char* what() const throw()
	  {
		std::cerr << "Simultaneous stimulations on the same channel might occur. Check your json file:" + file << std::endl;
	    return "";
	  }
};

}
}


