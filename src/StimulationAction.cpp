#include "StimulationAction.h"
#include "errors/StimulationException.h"


StimulationAction::StimulationAction(): stimulating(false){}

void StimulationAction::init(Channel* channel){
	setChannel(channel);
}

void StimulationAction::stimulate(){
	stimulating = true;
}

void StimulationAction::setChannel(Channel* nChannel){
	if(nChannel == nullptr){
		throw new stim::errors::NullptrChannelException();
	}
	channel = nChannel;
}
