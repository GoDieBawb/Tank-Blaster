/**
 * Source File: obosaO.cpp
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 **/

//#include "./entity/unit/Behavior.cpp"
#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

struct BoxBehavior : public Behavior {
  void behave (Node &model);
  BoxBehavior();
  int box = rand() % 2;
};

void BoxBehavior::behave (Node &model) {
  Tank &tank = (Tank&) model;

  while(1) {
	  if (box == 0) {
		tank.moveUp();
		box = 2;
	} else if (box == 1) {
		tank.moveUpRight();
		box = 2;
	}
	  
   if (tank.location.x <= WINDOWS_WIDTH) {
	    tank.moveUpRight();
		}
	else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) &&
		tank.location.y > (WINDOWS_HEIGHT/2)) {
		tank.moveLeft();
	}

	if (tank.location.x <= (WINDOWS_WIDTH - 20) && tank.location.y <= 
		(WINDOWS_HEIGHT/2)) {
		tank.moveUp();
	}
	else if (tank.location.x < (WINDOWS_WIDTH - 20) && tank.location.y >
		(WINDOWS_HEIGHT/2)) {
		tank.moveDown();
	}
 
  }
}
