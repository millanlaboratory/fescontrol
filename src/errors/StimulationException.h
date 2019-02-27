#pragma once
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception
#include <string>     // std::string, std::to_string

namespace stim{
namespace errors{

class StimulatorException : public std::exception{
public:
	StimulatorException(){}
	virtual const char* what() const throw(){
		return "Device could not be found ";
	}
};

class StimulatorFrequencyException : public StimulatorException{
public:
	StimulatorFrequencyException(int nFrequency):frequency(nFrequency){}

	virtual const char* what() const throw(){
		return ("Could not update stimulator frequency with value " + std::to_string(frequency)).c_str();
	}
	int frequency;
};

class ChannelNotInStimulatorException : public std::exception{
public:
	ChannelNotInStimulatorException(int nchannelNumber):channelNumber(nchannelNumber){}
	virtual const char* what() const throw(){
		return ("No channel at this number " + std::to_string(channelNumber)).c_str();
	}

	int channelNumber;
};

class NullPtrActionException : public std::exception{
public:
	NullPtrActionException(){}
	virtual const char* what() const throw(){
		return "Stimulation action is a nullptr. For safety reasons, it should not be empty.";
	}
};

class NullptrChannelException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Channel is a nullptr. For safety reasons, it should not be empty.";
	}
};

class NegativeCurrentException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Trying to init current for SetterAction with negative value.";
	}
};

class NegativePulseWidthException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Trying to init pulseWidth for SetterAction with negative value.";
	}
};

class NullptrIncrementerException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Incrementer is a nullptr. For safety reasons, it should not be empty.";
	}
};

class TwoIncrementersException : public std::exception{
public:
	TwoIncrementersException(int nNbIncrementers): nbIncrementers(nNbIncrementers){}
	virtual const char* what() const throw(){
		return ("Two incrementers are needed " + std::to_string(nbIncrementers) + " are given.").c_str();
	}

	int nbIncrementers;
};

class TwoDecrementersException : public std::exception{
public:
	TwoDecrementersException(int nNbDecrementers): nbDecrementers(nNbDecrementers){}
	virtual const char* what() const throw(){
		return ("Two decrementers are needed " + std::to_string(nbDecrementers) + " are given.").c_str();
	}

	int nbDecrementers;
};

class IncrementerException : public std::exception{
public:
	IncrementerException(std::string type): incrementer(type){}
	virtual const char* what() const throw(){
		return ("Type " + incrementer + " is not a valid incrementer type.").c_str();
	}

	std::string incrementer;
};

class WrongParametersException : public std::exception{
public:
	WrongParametersException(int nexpected, int nobtained):expected(nexpected), obtained(nobtained){

	}
	virtual const char* what() const throw(){
		return ("Wrong number of parameters for incrementer. Expected " +
				std::to_string(expected) +
				", obtained " +
				std::to_string(obtained)).c_str();
	}

	int expected;
	int obtained;

};

}
}
