//Name: James Kim
//Description: Enemy behavior patters
//Course: CMPS3350
//Date: 2/24/17

#//include "../Behavior.cpp"
#include "time.h"
#include <stdlib.h>
//#include "util/GIUtils.cpp"

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

struct SpiralBehavior : public Behavior {

    time_t lastAct; //Time for last act
    int spiral; //random true or false to determine go left or right first
    void behave (Node &model);
    SpiralBehavior();
};

SpiralBehavior::SpiralBehavior() {
    //Initialize
    lastAct = time(0);
    spiral = rand() % 2;
}

/*struct HourglassBehavior : public Behavior {
    void behave (Node &model);
};

HourglassBehavior::HourglassBehavior() {
}*/

void SpiralBehavior::behave (Node &model) {

    Tank &tank = (Tank&) model;

    if (spiral == 0) {
	tank.moveUpLeft();
	spiral = 2;
    }
    else if (spiral == 1) {
	tank.moveUpRight();
	spiral = 2;
    }

   // while ("tank is alive") {
	if (tank.location.x <= (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) && 
		tank.location.y <= (WINDOWS_HEIGHT/2)) {
	    tank.moveUpRight();
	}
	else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) && 
		tank.location.y > (WINDOWS_HEIGHT/2)) {
	    tank.moveDownRight();
	}

	if (tank.location.x <= (WINDOWS_WIDTH - 20) && tank.location.y <= 
		(WINDOWS_HEIGHT/2)) {
	    tank.moveUpLeft();
	}
	else if (tank.location.x < (WINDOWS_WIDTH - 20) && tank.location.y >
		(WINDOWS_HEIGHT/2)) {
	    tank.moveDownLeft();
	}

	if (tank.location.x <= (WINDOWS_HEIGHT - (WINDOWS_HEIGHT * 0.9)) && 
		tank.location.y <= (WINDOWS_WIDTH/2)) {
	    tank.moveDownRight();
	}
	else if (tank.location.y < (WINDOWS_HEIGHT - (WINDOWS_HEIGHT * 0.9)) && 
		tank.location.x > (WINDOWS_WIDTH/2)) {
	    tank.moveDownLeft();
	}

	if (tank.location.y <= (WINDOWS_HEIGHT - 20) && tank.location.x <= 
		(WINDOWS_WIDTH/2)) {
	    tank.moveUpRight();
	}
	else if (tank.location.y < (WINDOWS_HEIGHT - 20) && tank.location.x > 
		(WINDOWS_WIDTH/2)) {
	    tank.moveUpLeft();
	}
   // }
}

//void HourglassBehavior::behave (Node &model) {
//    Tank &tank = (Tank&) model;
//}
