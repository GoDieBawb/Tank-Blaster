#include "time.h"

struct StreetAttackBehavior : public Behavior {
	
	time_t lastShot; //Time for last act
	bool inPos; //bool to whether to stop
	void behave(Node &model); 
	StreetAttackBehavior();
};

StreetAttackBehavior::StreetAttackBehavior() {
	//Initialize
	lastShot = time(0);
}

void StreetAttackBehavior::behave(Node &model) {

	Tank &tank = (Tank&) model;

	if (!inPos) {

		tank.moveUp();

		if (tank.location.y > WINDOW_HEIGHT*.75) {
			inPos=true;		
		}

		return;

	}	

	if (time(0) - lastShot > 5) {
		//printf("shoot\n");
		//Set last act to now
		lastShot = time(0);
		tank.shoot();
	}

}
