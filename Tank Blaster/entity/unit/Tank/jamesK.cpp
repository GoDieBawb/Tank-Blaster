#include "../Behavior.cpp"
#include "time.h"

struct SpiralBehavior : public Behavior {

    	time_t lastAct; //Time for last act
	bool spiral; //bool to determine go left or right first
	void behave (Node &model);
	SpiralBehavior();
};

SpiralBehavior::SpiralBehavior() {
    	//Initialize
	lastAct = time(0);
}

void SpiralBehavior::behave (Node &model) {
    	
    	Tank &tank = (Tank&) model;

	if (time(0) - lastAct > 10) {
	    	
	    	lastAct = time(0);

		if (spiral)
		    spiral = false;
		else
		    spiral = true;
	}

	if (spiral) {
	    	//need to add more later to have full spiral
	    	tank.moveUpleft();
	}
	else {
	    	tank.moveUpRight();
	}
}
