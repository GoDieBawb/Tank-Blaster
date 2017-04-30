#define MAX_PARTICLES 5000
#define GRAVITY 	  0.01
#define rnd() (float)rand() / (float)RAND_MAX
#include "time.h"

bool 		checkEscape();	//Checks for Exit Condition
GlUtils		gu; 			//Gl Utility Holds Gl Functions

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

	initSound();
	doMusic();
	game.entm.pm.player.initTank();

	/******************************/

	//Initialize Gl Utility
	gu.initXWindows();
	gu.init_opengl();

	game.rootNode.attachChild(game.entm.fm.leftTower);
	game.rootNode.attachChild(game.entm.fm.rightTower);

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
		//Check for escape condition
		checkEscape();

		t   = clock() - t;
		tpf = double(t) / CLOCKS_PER_SEC * 1000;


	}

	//Cleanup GL Utility
	gu.cleanupXWindows();
	cleanUpSound();
	
	//Exit
	return 0;

}

bool checkEscape() {

	//If Interaction Manager has Escape Pressed
	//Return true
	if (game.im.esc) {
		return true;		
	}

	return false;

}
