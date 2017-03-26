/**
 * Source File: obosaO.cpp
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 * SECTIONS:    1. Top Bar - upper most bar for heads up display
 *              2. Box Behavior - give tanks a box-like movement behavior
 **/

#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

struct HUD: public Shape {
  Shape height, width;
  Vec color, location;
};

struct BoxBehavior : public Behavior {
  void behave (Node &model);
  BoxBehavior();
};

// =============================================================================
// SECTION::Top Bar / FIXME -- incorrect object instantiation
// -----------------------------------------------------------------------------
/*HUD topBar;
topBar.width    = WINDOWS_WIDTH;
topBar.height   = WINDOWS_HEIGHT/10;
topBar.color    = blue;
topBar.location = Vec(WINDOWS_WIDTH/2, WINDOWS_HEIGHT-topBar.height, 0);
attachChild(topBar);*/

// =============================================================================

// =============================================================================
// SECTION::Box Behavior
// -----------------------------------------------------------------------------

void BoxBehavior::behave (Node &model) {
  Tank &tank = (Tank&) model;
  int box = rand() % 2;

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

// =============================================================================
