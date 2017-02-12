#include "Behavior.cpp"
#include "time.h"

struct ZigZagBehavior : public Behavior {
	
	time_t lastAct;
	bool zig;
	void behave(Node &model);
	ZigZagBehavior();
};

ZigZagBehavior::ZigZagBehavior() {
	lastAct = time(0);
}

void ZigZagBehavior::behave(Node &model) {

	Tank &tank = (Tank&) model;

	if (time(0) - lastAct > 5) {

		lastAct = time(0);

		if (zig)
			zig = false;
		else
			zig = true;

	}

	if (zig) {
		tank.moveUpLeft();
	}

	else {
		tank.moveUpRight();
	}

}
