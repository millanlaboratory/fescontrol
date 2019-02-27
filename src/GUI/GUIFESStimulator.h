
#pragma once
#include "../FESStimulator.h"

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif

class GUIFESStimulator : public FESStimulator{
public:
	GUIFESStimulator();
	virtual ~GUIFESStimulator();
	void update(float dt);

private:
    // Class data
	std::vector<std::vector<double>> data;
	std::vector<std::vector<double>> time;
    const unsigned int NSIZE;
    const unsigned int NCHANNEL;
    double t;
};

