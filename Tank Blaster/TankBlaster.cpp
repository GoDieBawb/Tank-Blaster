#define MAX_PARTICLES 5000
#define GRAVITY 	  0.01
#define rnd() (float)rand() / (float)RAND_MAX

Game 		game; 			//Game struct defined in util/GameDef.h
bool 		checkEscape();	//Checks for Exit Condition
GlUtils		gu; 			//Gl Utility Holds Gl Functions


//Main Function
int main() {

	//Initialize Gl Utility
	gu.initXWindows();
	gu.init_opengl();

	Car car( Vec(400,400,0));
	game.rootNode.attachChild(car);

	Tower tower( Vec(100,100,0));
	game.rootNode.attachChild(tower);

	while (!checkEscape()) {

		//Update Interaction Manager
		game.im.update(gu.dpy);
		//Update Entity Manager
		game.entm.update();
		//Render Game
		gu.render(game);
		//Check for escape condition
		checkEscape();

	}

	//Cleanup GL Utility
	gu.cleanupXWindows();

	//Exit
	return 0;

}

bool checkEscape() {

	//If Interaction Manager has Excaped Pressed
	//Return true
	if (game.im.esc) {
		return true;		
	}

	return false;

}
