/*
 * Application.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: cnbiadministrator
 */

#include "Application.h"


Application::Application(bool nVerbose):
verbose(nVerbose){

}

Application::~Application(){
	delete stimulator;
	delete reader;
}

void Application::updateStimulator() {
	auto currentEpoch = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedMilliSeconds = (currentEpoch - previousEpoch) * 1000;
	if (elapsedMilliSeconds.count() > 300) {
		stimulator->update(elapsedMilliSeconds.count());
		previousEpoch = currentEpoch;
		done = stimulator->areActionsComplete();
		/*if (verbose)
			std::cerr << "Refreshing time: " << elapsedMilliSeconds.count() << std::endl;*/
	}
}

void Application::runApplication() {
	previousEpoch = std::chrono::system_clock::now();
	done = stimulator->areActionsComplete();
	while (!done) {
		updateStimulator();
	}
}

void Application::start(std::string fileName){
	std::vector<StimulationAction*> actions = reader->getSequenceFromJsonFile(fileName);
	for(unsigned int actionIndex(0); actionIndex < actions.size(); ++actionIndex){
		stimulator->addStimulationAction(actions[actionIndex]);
	}
	if(verbose)
		std::cerr << "Initializing stimulator" << std::endl;

	stimulator->start();
	if(verbose)
		std::cerr << "Running stimulator" << std::endl;
	runApplication();
}

void Application::initStimulator() {
	SerialPort* serialPort = new SerialPort();
	sp_tty* device = new sp_tty();
	stimulator->init(serialPort, device);
	for (unsigned int i(0); i < CHANNELS_QUANTITY; ++i) {
		stimulator->addChannel(new Channel(device, serialPort, i + 1, verbose));
	}
}

void Application::init(FESStimulator* nStim, FESJsonReader* nRead){
	stimulator = nStim;
	reader = nRead;
	reader->init(stimulator, new StimulationActionFactory());
	initStimulator();
}
