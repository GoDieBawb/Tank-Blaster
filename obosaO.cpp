/**
 * Name:        Obosa Osagie-Amayo
 * Description: Obosa Osagie-Amayo's code for Tank Blaster
 **/

#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

// Player Manager ==============================================================

// Constructor initializes data members
PlayerManager::PlayerManager(InteractionManager &i) {

	// Name Player Node
	playerNode.name = "Player Node";
	// Attach player tank to player node
	playerNode.attachChild(player.tank);
	// Set interaction manager
	im = &i;

}

// Uses InteractionManager to listen for key presses
void PlayerManager::actOnKeys() {

	Tank* tank = &player.tank;

	if (im->up && im->left) {
		tank->moveUpLeft();
	}

	else if (im->up && im->right) {
		tank->moveUpRight();
	}

	else if (im->up) {
		tank->moveUp();
	}

	else if (im->down && im->left) {
		tank->moveDownLeft();
	}

	else if (im->down && im->right) {
		tank->moveDownRight();
	}

	else if (im->down) {
		tank->moveDown();
	}

	else if (im->left) {
		tank->moveLeft();
	}

	else if (im->right) {
		tank->moveRight();
	}

	if (im->space) {
		bullets[bulletCount] = tank->shoot();
		bulletCount++;
		im->space = false;
                doShoot();
	}

}

// Called on Update Loop
void PlayerManager::update() {
	actOnKeys();
    //checkPlayerHealth();
}

void Hud::checkCarCount() {
  int carsLeft = game.entm.pm.player.carsLeft;

  if (carsLeft == 2) {
    // do something
    hudNode.detachChild(car1); 
  }
}

void Hud::checkForRestart() {
  if (game.im.enter) {
    Player player = game.entm.pm.player;
    player.score = 0;
    player.health = 3;
    player.isDead = false;

    hudNode.detachChild(promptShape); 
  }  
}


// HUD =========================================================================
Hud::Hud(Node &rootNode) : lifeDisplay(Vec(0, 0, 0)), lifeDisplay2(Vec(30, 0, 0)), lifeDisplay3(Vec(60, 0, 0)),
  car1(Vec(0, 0, 0)), car2(Vec(0, 0, 0)), car3(Vec(0, 0, 0))
{

	lifeDisplay.location.x  = -WINDOW_WIDTH/2 + lifeDisplay.body.width;
	lifeDisplay2.location.x = -WINDOW_WIDTH/2 + (lifeDisplay2.body.width*2);
	lifeDisplay3.location.x = -WINDOW_WIDTH/2 + (lifeDisplay3.body.width*3);

    // Angles
    car1.angle = 90;
    car2.angle = 90;
    car3.angle = 90;
    // Colors
    car1.body.color  = blue;
	car1.front.color = blue;
	car1.back.color  = blue;

    car2.body.color  = green;
	car2.front.color = green;
	car2.back.color  = green;

    car3.body.color  = red;
	car3.front.color = red;
	car3.back.color  = red;
    // Location
	car1.location.x = WINDOW_WIDTH/2 - car1.body.width*2;
	car2.location.x = WINDOW_WIDTH/2 - car2.body.width*3;
	car3.location.x = WINDOW_WIDTH/2 - car3.body.width;

	bar.width  = WINDOW_WIDTH;
	bar.height = WINDOW_HEIGHT/10;
	bar.color  = Vec(201,208,201);
	bar.angle  = 0;

	hudNode.location.y  = WINDOW_HEIGHT - WINDOW_HEIGHT/20;
	hudNode.location.x  = WINDOW_WIDTH/2;
	hudNode.attachChild(bar);
	hudNode.attachChild(lifeDisplay);
	hudNode.attachChild(lifeDisplay2);
	hudNode.attachChild(lifeDisplay3);
	hudNode.attachChild(car1);
	hudNode.attachChild(car2);
	hudNode.attachChild(car3);

	textShape.width      = WINDOW_WIDTH/5;
	textShape.height     = WINDOW_HEIGHT/10;
	textShape.location.x = WINDOW_WIDTH/5;
	textShape.location.y = WINDOW_HEIGHT;

	promptShape.width  = WINDOW_WIDTH/3;
	promptShape.height = WINDOW_HEIGHT/5;
	promptShape.color  = Vec(201, 208, 201);
	promptShape.location = Vec(0, -WINDOW_HEIGHT/2, 0);
	promptShape.angle  = 0;
	promptShape.name = "Prompt";

    hudNode.attachChild(promptShape);
	rootNode.attachChild(hudNode);

}

void Hud::checkGameState() {
	bool isDead = game.entm.pm.player.isDead;
	if (isDead) {
      if (hudNode.hasChild(promptShape)) {
//        prompt();
	  }
   
      checkForRestart();
    }
}

void Hud::prompt() {
  hudNode.attachChild(promptShape);
}

void Hud::writeTestText() {
	Rect r = boxToRect(textShape);
	ggprint8b(&r, 32, 0x00dddd00, "Tank Blaster");
}

void Hud::update() {
	writeTestText();
    checkCarCount();
	checkGameState();
}

Rect boxToRect(Shape &s) {

	Rect rect;
	rect.centerx = s.location.x;
	rect.centery = s.location.y;
	rect.width	 = s.width;
	rect.height  = s.height;
	rect.bot	   = s.location.y - s.height/2;
	rect.top 	   = s.location.y + s.height/2;
	rect.left    = s.location.x - s.width/2;
	rect.right   = s.location.x + s.width/2;

	return rect;
}

// Tank Behaviors ==============================================================

// Box Behavior
struct BoxBehavior : public Behavior {
  void behave (Node &model);
  BoxBehavior();
};

void BoxBehavior::behave (Node &model) {
  Tank &tank = (Tank&) model;
  int box = rand() % 2;

  while(1) {
	  if (box == 0) {
      tank.moveUp();
      box = 2;
    }
    else if (box == 1) {
      tank.moveUpRight();
      box = 2;
    }

    if (tank.location.x <= WINDOWS_WIDTH) {
      tank.moveUpRight();
    }
    else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) &&
      tank.location.y > (WINDOWS_HEIGHT/2)) {
      tank.moveLeft();
    }

    if (tank.location.x <= (WINDOWS_WIDTH - 20) &&
      tank.location.y <= (WINDOWS_HEIGHT/2)) {
      tank.moveUp();
    }
    else if (tank.location.x < (WINDOWS_WIDTH - 20) &&
      tank.location.y > (WINDOWS_HEIGHT/2)) {
      tank.moveDown();
    }
  }
}


// Left, Right Behavior
struct LeftRightBehavior: public Behavior {
  void behave (Node &model);
  //BoxBehavior();
};

void LeftRightBehavior::behave (Node &model) {
  Tank &tank = (Tank&) model;
  int box    = rand() % 2;

  while(1) {
	  if (box == 0) {
      tank.moveLeft();
      box = 2;
    }
    else if (box == 1) {
      tank.moveRight();
      box = 2;
    }

    if (tank.location.x == WINDOWS_WIDTH - 20) {
      tank.moveLeft();
    }
    else if (tank.location.x == (WINDOWS_WIDTH-WINDOWS_WIDTH) + 20) {
      tank.moveRight();
    }
  }
}
