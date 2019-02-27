/*
 * GUIFESStimulator.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: cnbiadministrator
 */

#include "GUIFESStimulator.h"
#include "../matplotlibcpp.h"
#include <cmath>

using namespace std;
namespace plt = matplotlibcpp;

GUIFESStimulator::GUIFESStimulator():
		FESStimulator(true),
		NSIZE(50),
		NCHANNEL(8),
		t(0)
{
	for(unsigned int channel(0); channel < NCHANNEL; ++channel){
		data.push_back(std::vector<double>());
		time.push_back(std::vector<double>());
	}

}

GUIFESStimulator::~GUIFESStimulator(){
}

void GUIFESStimulator::update(float dt){
	FESStimulator::update(dt);
	t += dt/1000;
	plt::clf();
	for(unsigned int channel(0); channel < NCHANNEL; ++channel){
		if(data[channel].size() > NSIZE){
			data[channel].erase(data[channel].begin());
			time[channel].erase(time[channel].begin());
		}
		data[channel].push_back(getChannelByChannelNumber(channel+1)->getCurrent() + (channel + 0.5) * MAX_CURRENT);
		time[channel].push_back(t);
		plt::plot(time[channel], data[channel]);
	}
	plt::xlabel("Time (s)");
	plt::xlim(time[0][0], time[0][0] + NSIZE*dt/1000);
	plt::pause(0.01);
}
