//Name: James Kim
//Description: Enemy behavior patters
//Course: CMPS3350
//Date: 2/24/17

#include "time.h"
#include <stdlib.h>

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 600

struct Enemy {
	Behavior* behavior;
	Node*	  model;
	Enemy(Node& n, Behavior& b);
	int health;
	int lane;
};

Enemy::Enemy(Node& n, Behavior& b) {
	model 	 = &n;
	behavior = &b;
	health   = 3;
}

//Enemy Manager will handle enemies and enemy behavior
class EnemyManager {

	private:
		void   move();
		void   init();

	public:
		int  enemyCount;
		void update();
		Node enemyNode;
		EnemyManager();
		Enemy* enemies[12];	
		bool lanes[6];
		int minlane;
		int maxlane;
};

//Constructor initializes data memebrs
EnemyManager::EnemyManager() {
	enemyCount 	   = 0;
	enemyNode.name = "Enemy Node";
}

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

void EnemyManager::move() {

	for (int j = 0; j < 6; j++) {
		//Create an enemy if not enough
		if (enemyCount < 6) {

			if (lanes[j] == false) {
				//Randomize location
				int x = 800 - ((j * 100) + 145);
				//int y = 0 + (rand() % (int) (500 - 0 + 1));
				//int minlane = 800 - ((j * 100) + 95);
				//int maxlane = 800 - ((j * 100) + 195);

				//Local Variable put on heap
				Tank* 				  t = new Tank(Vec(x,0,0));
				StreetAttackBehavior* b = new StreetAttackBehavior();
				Enemy* 				  e = new Enemy(*t,*b);
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

//Called on Loop
void EnemyManager::update() {
	move();
}

struct SpiralBehavior : public Behavior {
    time_t lastAct; //Time for last act
    int spiral; //random true or false to determine go left or right first
    void behave (Node &model);
    SpiralBehavior();
};

SpiralBehavior::SpiralBehavior() {
    //Initialize
    lastAct = time(0);
    spiral = rand() % 2;
}

void SpiralBehavior::behave (Node &model) {

    Tank &tank = (Tank&) model;

    if (spiral == 0) {
	tank.moveUpLeft();
	spiral = 2;
    }
    else if (spiral == 1) {
	tank.moveUpRight();
	spiral = 2;
    }

	if (tank.location.x <= (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) && 
		tank.location.y <= (WINDOWS_HEIGHT/2)) {
	    tank.moveUpRight();
	}
	else if (tank.location.x < (WINDOWS_WIDTH - (WINDOWS_WIDTH * 0.9)) && 
		tank.location.y > (WINDOWS_HEIGHT/2)) {
	    tank.moveDownRight();
	}

	if (tank.location.x <= (WINDOWS_WIDTH - 20) && tank.location.y <= 
		(WINDOWS_HEIGHT/2)) {
	    tank.moveUpLeft();
	}
	else if (tank.location.x < (WINDOWS_WIDTH - 20) && tank.location.y >
		(WINDOWS_HEIGHT/2)) {
	    tank.moveDownLeft();
	}

	if (tank.location.x <= (WINDOWS_HEIGHT - (WINDOWS_HEIGHT * 0.9)) && 
		tank.location.y <= (WINDOWS_WIDTH/2)) {
	    tank.moveDownRight();
	}
	else if (tank.location.y < (WINDOWS_HEIGHT - (WINDOWS_HEIGHT * 0.9)) && 
		tank.location.x > (WINDOWS_WIDTH/2)) {
	    tank.moveDownLeft();
	}

	if (tank.location.y <= (WINDOWS_HEIGHT - 20) && tank.location.x <= 
		(WINDOWS_WIDTH/2)) {
	    tank.moveUpRight();
	}
	else if (tank.location.y < (WINDOWS_HEIGHT - 20) && tank.location.x > 
		(WINDOWS_WIDTH/2)) {
	    tank.moveUpLeft();
	}
}

