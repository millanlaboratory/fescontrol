#pragma once

class Incrementer {
public:
	Incrementer():duration(0), called(false){};
	Incrementer(double duration):duration(duration), called(false){};
	virtual ~Incrementer(){}
	virtual double getIncrement(float dt, float currentValue) = 0;
	virtual double getDecrement(float dt, float currentValue) = 0;
	virtual double getDuration(){return duration;}
	virtual bool calledOnce(){return called;}

	virtual Incrementer* getDecrementer() = 0;

protected:
	double duration;
	bool called;
};

