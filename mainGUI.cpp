/*
 * main.cpp
 *
 *  Created on: Oct 4, 2017
 *      Author: cnbiadministrator
 */

#include "src/Application.h"
#include "src/GUI/GUIFESStimulator.h"

class MainArgumentException : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Not enough arguments. Need a file name: ./fesjson \"file.json\"";
	}
};

int main(int argc, const char* argv[]){
	if(argc < 2){
		throw new MainArgumentException();
	}

	Application* app = new Application(true);

	try{
		app->init(new GUIFESStimulator(), new FESJsonReader());
		app->start(argv[1]);
	}
	catch(std::exception* e){
		std::cerr << e->what() << std::endl;
		delete e;
	}
	delete app;
	return 0;
}
