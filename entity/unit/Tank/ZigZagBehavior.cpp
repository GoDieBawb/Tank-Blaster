#include "time.h"

struct ZigZagBehavior : public Behavior {
	
	time_t lastAct; //Time for last act
	bool zig; //bool to determine zig or zag
	void behave(Node &model); 
	ZigZagBehavior();
};

ZigZagBehavior::ZigZagBehavior() {
	//Initialize
	lastAct = time(0);
}

//Behave takes in the model of behavior holder
//This is run on a loop
void ZigZagBehavior::behave(Node &model) {

	//Zig Zag Behavior is for a tank
	//Therefore we know that this specific
	//Nodes address contains a tank
	Tank &tank = (Tank&) model;

	//If the curent time in seconds minus
	//The previous action is greater than 5
	//5 seconds has passed since lastAct
	if (time(0) - lastAct > 5) {

		//Set last act to now
		lastAct = time(0);

		//Depending on zig or zag change
		if (zig)
			zig = false;
		else
			zig = true;

	}

	//If zig move up left
	if (zig) {
		tank.moveUpLeft();
	}

	//If zag move up right
	else {
		tank.moveUpRight();
	}

}
