/**
 * Source File: obosaO.cpp
 * Description: Move tank in a block pattern.
 * Course:      CMPS 3350
 * Lab:         5
 * Date:        2/23/2017
 **/

#include "./entity/unit/Behavior.cpp"
#include "time.h"

struct UpDownLeftRightBehavior : public Behavior {
  void behave (Node &model);
  UpDownLeftRightBehavior();
};

void UpDownLeftRightBehavior::behave (Node &model) {
  Tank &tank = (&Tank) model;
  
  int top    = WINDOW_HEIGHT - 20;
  int bottom = WINDOW_HEIGHT - WINDOW_HEIGHT;
  int left   = (WINDOW_WIDTH - WINDOW_WIDTH) + 20;
  int right  = WINDOW_WIDTH  - 20;

  while(1) {
	  
    switch(tank.body.location) {
      case (location.y < top):
        tank.moveUp();
        break;
      case (location.y > bottom):
        tank.moveDown();
        break;
      case (location.x > left):
        tank.moveLeft();
        break;
      case (location.x < right):
        tank.moveRight();
        break;
      default: // do nothing
        break;
    }
    
  }
}
