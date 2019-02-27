/*
 * mainConnectedFES.cpp
 *
 *  Created on: Oct 20, 2017
 *      Author: cnbiadministrator
 */




/*
 * main.cpp
 *
 *  Created on: Oct 4, 2017
 *      Author: cnbiadministrator
 */

#include "src/ConnectedApplication.h"
#include "src/GUI/GUIFESStimulator.h"
#include <getopt.h>
#include <iostream>

void usage(void) {
  printf("Usage: fesControlGUI [OPTION]...\n\n");
  printf("  -f       movement authorizer file in .json (resources/AuthorizedMovements.json default)\n");
  printf("  -n       iD bus name for event receiver (/dev default)\n");
  printf("  -h       display this help and exit\n");

  CcCore::Exit(1);
}

int main(int argc, char* argv[]){
	int opt;
	std::string receiverName("/dev");
	std::string authorizerFile("resources/AuthorizedMovements.json");
	while((opt = getopt(argc, argv, "f:n:h")) != -1) {
	    if(opt == 'f') {
	    	authorizerFile.assign(optarg);
	    } else if(opt == 'n') {
	    	receiverName.assign(optarg);
	    }
	    else if(opt == 'h'){
	    	usage();
	    	return 0;
	    }
	 }
	ConnectedApplication* app = new ConnectedApplication(true);

	MovementAuthorizer* movementAuthorizer = new MovementAuthorizer();
	movementAuthorizer->setFileName(authorizerFile);
	try{
		app->init(new CcCoreInstance(),
				new ClTobiIdInstance(ClTobiId::GetOnly, 3.0, receiverName),
				new ClLoopInstance(),
				new GUIFESStimulator(),
				new FESJsonReader(),
				movementAuthorizer);
		app->start();
	}
	catch(std::exception* e){
		std::cerr << e->what() << std::endl;
		delete e;
	}
	delete app;
	CcCore::Exit(EXIT_SUCCESS);
	return 0;
}
