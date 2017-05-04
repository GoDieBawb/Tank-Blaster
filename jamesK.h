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
		void clearEnemies();
		Node enemyNode;
		EnemyManager();
		Enemy* enemies[20];	
		bool lanes[6];
};
