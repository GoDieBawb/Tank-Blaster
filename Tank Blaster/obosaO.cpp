/**
 * Source File: obosaO.cpp
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 **/

//#include "./entity/unit/Behavior.cpp"

struct BoxBehavior : public Behavior {
  void behave (Node &model);
  BoxBehavior();
};

void BoxBehavior::behave (Node &model) {
  Tank &tank = (Tank&) model;
  
  //int top    = WINDOW_HEIGHT - 20;
  //int bottom = WINDOW_HEIGHT - WINDOW_HEIGHT;
  //int left   = (WINDOW_WIDTH - WINDOW_WIDTH) + 20;
  //int right  = WINDOW_WIDTH  - 20;

  while(1) {
	  
/*   switch(tank.body.location) {
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
    }
*/
      tank.moveUp();
 
  }
}
