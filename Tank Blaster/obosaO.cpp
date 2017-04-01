/**
 * Source File: obosaO.cpp
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 * SECTIONS:    1. Top Bar - upper most bar for heads up display
 *              2. Box Behavior - give tanks a box-like movement behavior
 **/

#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

// =============================================================================
// SECTION::Top Bar / FIXME -- incorrect object instantiation
// -----------------------------------------------------------------------------

class HUD: public Node {
  public:
    Shape topBar;
    HUD();
    HUD(Vec loc);
};

HUD::HUD(Vec loc) {
  Vec lightgray(70, 70, 70);

  // Top Bar
  topBar.width    = WINDOWS_WIDTH;
  topBar.height   = WINDOWS_HEIGHT/10;
  topBar.color    = lightgray;

  topBar.location = Vec(WINDOWS_WIDTH/2, WINDOWS_HEIGHT-topBar.height, 0);
  topBar.name = "Top HUD";

  // Attach other elements after Top Bar
  attachChild(topBar);
  angle = 0;
  location = loc;
}


// =============================================================================

// =============================================================================
// SECTION::Box Behavior
// -----------------------------------------------------------------------------

struct BoxBehavior : public Behavior {
  void behave (Node &model);
  BoxBehavior();
};

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









