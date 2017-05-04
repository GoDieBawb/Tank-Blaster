//Name: James Kim
//Description: Enemy behavior patters
//Course: CMPS3350
//Date Created: 2/24/17

//Set spawn points to each enemy so it doesnt spawn randomly at the bottom of the screen
//initialize behavior patteren to indiviual tanks
//give behaviors a bit more beef to fire back at player for added difficulty

//Constructor initializes data memebrs
EnemyManager::EnemyManager() {
	enemyCount 	   = 0;
	enemyNode.name = "Enemy Node";
}

struct StreetAttackBehavior : public Behavior {

	time_t lastShot; //Time for last act
	bool inPos; //bool to whether to stop
	void behave(Node &model);
	int randNum; 
	StreetAttackBehavior();
};

StreetAttackBehavior::StreetAttackBehavior() {
	//Initialize
	srand(time(NULL));
	lastShot = time(0);
	randNum = (rand() % 4) + 1;
}

void StreetAttackBehavior::behave(Node &model) {
	Tank &tank = (Tank&) model;
	Vec PlayerLoc = game.entm.pm.player.tank.location;
	if (!inPos) {
		if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		else
			tank.moveUp();

		if (tank.location.y > WINDOW_HEIGHT*.4) {
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
			inPos=true;
		}
		return;
	}
	
	if (time(0) - lastShot > 4) {
	//if (time(0) - lastShot > randNum) {
		//Set last act to now
		if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		lastShot = time(0);
		bullets[bulletCount]=tank.shoot();
		bulletCount++;
	}
}

struct SpiralBehavior : public Behavior {
	time_t lastShot; 
	int spiral; //random true or false to determine go left or right first
	bool inPos; 
	void behave (Node &model);
	SpiralBehavior (Node &model);
	int midlane;
	int minlane;
	int maxlane;
};

SpiralBehavior::SpiralBehavior(Node &model) {
	lastShot = time(0);
	spiral = rand() % 2;
	midlane = model.location.x;
	minlane = model.location.x - 50;
	maxlane = model.location.x + 50;
}

void SpiralBehavior::behave (Node &model) {

	Tank &tank = (Tank&) model;
	Vec PlayerLoc = game.entm.pm.player.tank.location;
	//start the tank by which direction
	if (!inPos) {
		if (spiral == 0) {
			tank.moveUpLeft();
			spiral = 2;
		}
		else if (spiral == 1) {
			tank.moveUpRight();
			spiral = 2;
		}
		//rest is just like a ball bouncing off walls in zigzag
		if (tank.location.x < minlane) {
			tank.moveUpRight();
		}
		else if (tank.location.x > maxlane) {
			tank.moveUpLeft();
		}
		if (tank.location.y > WINDOW_HEIGHT * .65) {
			inPos=true;		
		}
		if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		else
			tank.moveUp();

		if (tank.location.y > WINDOW_HEIGHT*.65) {
			inPos=true;		
		}
		return;
	}	

	if (time(0) - lastShot > 5) {
		if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		lastShot = time(0);
		bullets[bulletCount]=tank.shoot();
		bulletCount++;
	}
}

//go up to a certain point then go right then left then back right midway
//Making a "T"
struct TBehavior: public Behavior {
	time_t lastShot;
	bool inPos;
	void behave (Node &model);
	TBehavior (Node &model);
	int midlane;
	int minlane;
	int maxlane;
	bool checkpoint[5];
};

TBehavior::TBehavior(Node &model) {

	lastShot = time(0); 
	midlane = model.location.x;
	minlane = model.location.x - 50;
	maxlane = model.location.x + 50;

	for (int i = 0; i < 5; i++) {
		checkpoint[i] = false;
	}

}

void TBehavior::behave(Node &model) {
	Tank &tank 	  = (Tank&) model;
	Vec PlayerLoc = game.entm.pm.player.tank.location;
	while (!inPos) {
		tank.moveUp();
		while (checkpoint[0] == false) {
			if (tank.location.y == WINDOW_HEIGHT * .1) {
				tank.moveRight();
			}
			if (tank.location.x == maxlane) {
				tank.moveLeft();
			}
			if (tank.location.x == minlane) {
				tank.moveRight();
			}
			if (tank.location.x == midlane) {
				tank.moveUp();
				checkpoint[0] = true;
			}
		}
		while (checkpoint[1] == false) {
			if (tank.location.y == WINDOW_HEIGHT * .2) {
				tank.moveRight();
			}
			if (tank.location.x == maxlane) {
				tank.moveLeft();
			}
			if (tank.location.x == minlane) {
				tank.moveRight();
			}
			if (tank.location.x == midlane) {
				tank.moveUp();
				checkpoint[1] = true;
			}
		}
		while (checkpoint[2] == false) {
			if (tank.location.y == WINDOW_HEIGHT * .3) {
				tank.moveRight();
			}
			if (tank.location.x == maxlane) {
				tank.moveLeft();
			}
			if (tank.location.x == minlane) {
				tank.moveRight();
			}
			if (tank.location.x == midlane) {
				tank.moveUp();
				checkpoint[2] = true;
			}
		}
		while (checkpoint[3] == false) {
			if (tank.location.y == WINDOW_HEIGHT * .4) {
				tank.moveRight();
			}
			if (tank.location.x == maxlane) {
				tank.moveLeft();
			}
			if (tank.location.x == minlane) {
				tank.moveRight();
			}
			if (tank.location.x == midlane) {
				tank.moveUp();
				checkpoint[0] = true;
			}
		}
		while (checkpoint[4] == false) {
			if (tank.location.y == WINDOW_HEIGHT * .5) {
				tank.moveRight();
			}
			if (tank.location.x == maxlane) {
				tank.moveLeft();
			}
			if (tank.location.x == minlane) {
				tank.moveRight();
			}
			if (tank.location.x == midlane) {
				tank.moveUp();
				checkpoint[4] = true;
			}
		}
		if (tank.location.y > WINDOW_HEIGHT * .65) {
			inPos=true;		
		}
		if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		else
			tank.moveUp();

		if (tank.location.y > WINDOW_HEIGHT*.65) {
			inPos=true;		
		}
		return;
	}	

	if (time(0) - lastShot > 5) {
		if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		lastShot = time(0);
		bullets[bulletCount]=tank.shoot();
		bulletCount++;
	}
}

struct SnakeBehavior : public Behavior {

	time_t lastShot; //Time for last act
	bool inPos; //bool to whether to stop
	void behave(Node &model); 
	SnakeBehavior();
	SnakeBehavior(Node &model);
	int midlane;
	int minlane;
	int maxlane;
};

SnakeBehavior::SnakeBehavior() {
	//Initialize
	lastShot = time(0);
}

SnakeBehavior::SnakeBehavior(Node &model) {
	midlane = model.location.x;
	minlane = model.location.x - 50;
	maxlane = model.location.x + 50;
}

void SnakeBehavior::behave(Node &model) {
	Tank &tank = (Tank&) model;
	Vec PlayerLoc = game.entm.pm.player.tank.location;

	if (!inPos) {
		tank.moveLeft();
		while (time(0) - lastShot < 5) {
			tank.moveUp();
		}

		while (tank.location.x < minlane) {
			tank.moveRight();
			lastShot = time(0);
		}
		while (tank.location.x > maxlane) {
			tank.moveLeft();
			lastShot = time(0);
		}

		if (tank.location.y > WINDOW_HEIGHT*.65) {
			inPos=true;		
		}
		if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		else
			tank.moveUp();

		if (tank.location.y > WINDOW_HEIGHT*.65) {
			inPos=true;		
		}
		return;
	}	

	if (time(0) - lastShot > 5) {
		if (PlayerLoc.x < tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownLeft();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x > tank.location.x && PlayerLoc.y == tank.location.y) {
			tank.moveDownRight();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y < tank.location.y) {
			tank.moveDown();
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}

		else if (PlayerLoc.x == tank.location.x && PlayerLoc.y > tank.location.y) {
			lastShot = time(0);
			bullets[bulletCount]=tank.shoot();
			bulletCount++;
		}
		lastShot = time(0);
		bullets[bulletCount]=tank.shoot();
		bulletCount++;
	}

}

void EnemyManager::move() {

	for (int j = 0; j < 6; j++) {
		//Create an enemy if not enough
		if (enemyCount < 6) {

			if (lanes[j] == false) {
				//Set spawn points based on which enemy died
				int x = 800 - ((j * 100) + 145);

				//Local Variable put on heap
				Tank* t = new Tank(Vec(x,0,0));
				t->body.color = Vec(200,38,33);
				StreetAttackBehavior* b = new StreetAttackBehavior();
				Enemy* e = new Enemy(*t,*b);
				e->lane = j;
				//Add to list and render node
				enemies[enemyCount] = e;
				enemyNode.attachChild(*t);
				enemyCount++;
				lanes[j] = true;
			}
		}
		//Act on list of enemies
		for (int i = 0; i < enemyCount; i++) {
			enemies[i]->behavior->behave(*enemies[i]->model);
			if (enemies[i]->model->location.y > 600 || enemies[i]->health <= 0) {
				//Detach Child From Render Node
				enemyNode.detachChild(*enemies[i]->model);
				//Delete because tanks put on heap
				lanes[enemies[i]->lane] = false;
				doExplosion();
				game.entm.pm.player.score += 100;
				/*if (game.entm.pm.player.score % 5000 == 0) {
					game.entm.pm.player.health++;
				}*/
				delete enemies[i]->model;
				delete enemies[i]->behavior;
				delete enemies[i];
				//Remove Tank from List
				enemies[i] = enemies[enemyCount-1];
				enemyCount--;
			}
		}
	}
}

void EnemyManager::clearEnemies() {

	for (int i = 0; i < enemyCount; i++) {
		lanes[i] = false;
		enemyNode.detachChild(*enemies[i]->model);
		delete enemies[i]->model;
		delete enemies[i]->behavior;
		delete enemies[i];
		//Remove Tank from List
		enemies[i] = NULL;
	}

	enemyCount = 0;

}

//Called on Loop
void EnemyManager::update() {
	move();
}

//templete for behavior

struct aBehavior : public Behavior {

	time_t lastShot; //Time for last act
	bool inPos; //bool to whether to stop
	void behave(Node &model); 
	aBehavior();
	aBehavior (Node &model);
	int midlane;
	int minlane;
	int maxlane;
};

aBehavior::aBehavior() {
	//Initialize
	lastShot = time(0);
}

aBehavior::aBehavior(Node &model) {
	midlane = model.location.x;
	minlane = model.location.x - 50;
	maxlane = model.location.x + 50;
}

void aBehavior::behave(Node &model) {
	Tank &tank = (Tank&) model;
	//Vec PlayerLoc = game.entm.pm.player.tank.location;

	if (!inPos) {
		tank.moveUp();
		if (tank.location.y > WINDOW_HEIGHT*.65) {
			inPos=true;		
		}
		return;
	}	
	if (time(0) - lastShot > 5) {
		//Set last act to now
		lastShot = time(0);
		bullets[bulletCount]=tank.shoot();
		bulletCount++;
	}
}

