#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <math.h>
#include <cmath>

#include "scene/ShapeDefs.h"
#include "util/InteractionManager.cpp"
#include "util/GameDef.h"
#include "util/GlUtils.cpp"

#define MAX_PARTICLES 5000
#define GRAVITY 	  0.01
#define rnd() (float)rand() / (float)RAND_MAX

Game 		game; 			//Game struct defined in util/GameDef.h
bool 		checkEscape();	//Checks for Exit Condition
GlUtils		gu; 			//

//Main Function
int main() {
	
	gu.initXWindows();
	gu.init_opengl();

	Display *dpy = gu.dpy;

	while (!checkEscape()) {
		game.im.update(dpy);
		game.em.update();
		gu.render(game);
		checkEscape();
	}

	gu.cleanupXWindows();

	return 0;

}

bool checkEscape() {

	if (game.im.esc) {
		return true;		
	}

	return false;

}
