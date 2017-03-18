#include "../unit/Tank/StreetAttackBehavior.cpp"

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
		bool lanes[10];
};

//Constructor initializes data memebrs
EnemyManager::EnemyManager() {

	enemyCount 	   = 0;
	enemyNode.name = "Enemy Node";

}

void EnemyManager::move() {

	for (int j = 0; j < 10; j++) {
		//Create an enemy if not enough
		if (enemyCount < 10) {

			if (lanes[j] == false) {
				//Randomize location
				int x = 800 - ((j * 70) - 20);
				//int y = 0 + (rand() % (int) (500 - 0 + 1));


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

