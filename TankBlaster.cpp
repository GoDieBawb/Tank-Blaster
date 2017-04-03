#define MAX_PARTICLES 5000
#define GRAVITY 	  0.01
#define rnd() (float)rand() / (float)RAND_MAX
#include "time.h"

Game 		game; 			//Game struct defined in util/GameDef.h
bool 		checkEscape();	//Checks for Exit Condition
GlUtils		gu; 			//Gl Utility Holds Gl Functions
void makeStreet();

//Main Function
int main(int argc, char* argv[]) {

	/******************************/
	/**SomeLib approx 11.9 faster**/
	/******************************/
	osDiv = 1;
	if (argc > 1) {

		if (*argv[1] == 'u') {
			osDiv = 11.9;
		}

	}

	game.entm.pm.player.initTank();

	/******************************/

	//Initialize Gl Utility
	gu.initXWindows();
	gu.init_opengl();

	Tower leftTower( Vec(50,50,0));
	Tower rightTower( Vec(750,50,0));
	TowerBehavior left(0,50);
	TowerBehavior right(130,180);
	game.rootNode.attachChild(leftTower);
	game.rootNode.attachChild(rightTower);


	time_t t = clock();

	while (!checkEscape()) {
	
		t = clock();
		//std::cout << tpf << std::endl; 
		//Update Interaction Manager
		game.im.update(gu.dpy);
		//Update Entity Manager
		game.entm.update();
		//Render Game
		gu.render(game);
		left.behave(leftTower);
		right.behave(rightTower);
		//Check for escape condition
		checkEscape();

		t   = clock() - t;
		tpf = double(t) / CLOCKS_PER_SEC * 1000;


	}

	//Cleanup GL Utility
	gu.cleanupXWindows();

	//Exit
	return 0;

}

void makeStreet() {


}

bool checkEscape() {

	//If Interaction Manager has Excaped Pressed
	//Return true
	if (game.im.esc) {
		return true;		
	}

	return false;

}
