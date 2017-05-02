#define MAX_PARTICLES 5000
#define GRAVITY 	  0.01
#define rnd() (float)rand() / (float)RAND_MAX
#include "time.h"

bool 		checkEscape();	//Checks for Exit Condition
GlUtils		gu; 			//Gl Utility Holds Gl Functions

//Main Function
int main(int argc, char* argv[]) {

	initSound();
	doMusic();
	game.entm.pm.player.initTank();

	/******************************/

	//Initialize Gl Utility
	gu.initXWindows();
	gu.init_opengl();

	game.rootNode.attachChild(game.entm.fm.leftTower);
	game.rootNode.attachChild(game.entm.fm.rightTower);

	while (!checkEscape()) {
	
		//std::cout << tpf << std::endl; 
		//Update Interaction Manager
		game.im.update(gu.dpy);
		//Update Entity Manager
		if (!game.entm.pm.player.isDead)
			game.entm.update();
		//Render Game
		gu.render(game);
		//Check for escape condition
		checkEscape();

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
