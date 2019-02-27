#pragma once
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception

namespace channel{
namespace errors{

class ChannelException : public std::exception{
public:
	virtual const char* what() const throw()
	  {
	    return "Wrong Channel. Must be between 1 and 8";
	  }
};

class SerialPortException : public ChannelException{
public:
	virtual const char* what() const throw()
	  {
	    return "Serial Port variable shouldn't be nullptr.";
	  }
};

class TtyException : public ChannelException{
public:
	virtual const char* what() const throw()
	  {
	    return "Serial Port TTY variable shouldn't be nullptr.";
	  }
};

class StimulationException : public ChannelException{
public:
	virtual const char* what() const throw()
	  {
	    return "Failed to stimulate on channel.";
	  }
};

class ChannelParameterException : public ChannelException{
public:
	ChannelParameterException(double nValue): value(nValue){}
	virtual const char* what() const throw()
	  {
	    return "Wrong parameter value for stimulation. Got Expected current, frequency and pulse width to be positive.";
	  }
	double value;
};

}
}
