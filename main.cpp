#include "src/ConnectedApplication.h"
#include "src/GUI/GUIFESStimulator.h"
#include <getopt.h>
#include <iostream>

void usage(void) {
  printf("Usage: fesControlGUI [OPTION]...\n\n");
  printf("  -d       display information: verbose, gui or silent (default)\n");
  printf("  -f       movement authorizer file in .json (resources/AuthorizedMovements.json default)\n");
  printf("  -t       test movement file in .json \n");
  printf("  -n       iD bus name for event receiver (/dev default)\n");
  printf("  -h       display this help and exit\n");

  CcCore::Exit(1);
}

int main(int argc, char* argv[]){
	int opt;
	bool test(false);
	bool gui(false);
	bool verbose(false);

	std::string receiverName("/dev");
	std::string authorizerFile("resources/AuthorizedMovements.json");
	std::string testFile("");
	while((opt = getopt(argc, argv, "d:f:t:n:h")) != -1) {
	    if(opt == 'f') {
	    	authorizerFile.assign(optarg);
	    } else if(opt == 'n') {
	    	receiverName.assign(optarg);
	    }
	    else if(opt == 't'){
	    	test = true;
	    	testFile.assign(optarg);
	    }
	    else if(opt == 'd'){
	    	std::string optArgument;
	    	optArgument.assign(optarg);
			if(optArgument == "gui")
				gui = true;
			if(optArgument == "verbose")
				verbose = true;
		}
	    else if(opt == 'h'){
			usage();
			return 0;
		}
	}
	Application* app = nullptr;
	if(test)
		app = new Application(verbose);
	else
		app = new ConnectedApplication(verbose);

	try{
		FESStimulator* stimulator;
		if(gui){
			stimulator = new GUIFESStimulator();
		}
		else{
			stimulator = new FESStimulator(verbose);
		}
		if (test){
			app->init(stimulator, new FESJsonReader());
			app->start(testFile);
		}
		else{
			MovementAuthorizer* movementAuthorizer = new MovementAuthorizer();
			movementAuthorizer->setFileName(authorizerFile);
			((ConnectedApplication*)app)->init(new CcCoreInstance(),
					new ClTobiIdInstance(ClTobiId::GetOnly, 3.0, receiverName),
					new ClLoopInstance(),
					stimulator,
					new FESJsonReader(),
					movementAuthorizer);
			((ConnectedApplication*)app)->start();
		}
	}
	catch(std::exception* e){
		std::cerr << e->what() << std::endl;
		delete e;
	}
	delete app;
	return 0;
}


