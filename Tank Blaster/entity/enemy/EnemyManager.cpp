#include "../unit/Tank/StreetAttackBehavior.cpp"

struct Enemy {
	Behavior* behavior;
	Node*	  model;
	Enemy(Node& n, Behavior& b);
	int health;
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

};

//Constructor initializes data memebrs
EnemyManager::EnemyManager() {

	enemyCount 	   = 0;
	enemyNode.name = "Enemy Node";

}

void EnemyManager::move() {

	
	//Create an enemy if not enough
	if (enemyCount < 10) {

		//Randomize location
		int x = 0 + (rand() % (int) (800 - 0 + 1));
		//int y = 0 + (rand() % (int) (500 - 0 + 1));

		
		//Local Variable put on heap
		Tank* 				  t = new Tank(Vec(x,0,0));
		StreetAttackBehavior* b = new StreetAttackBehavior();
		Enemy* 				  e = new Enemy(*t,*b);

		//Add to list and render node
		enemies[enemyCount] = e;
		enemyNode.attachChild(*t);
		enemyCount++;

	}


	//Act on list of enemies
	for (int i = 0; i < enemyCount; i++) {

		enemies[i]->behavior->behave(*enemies[i]->model);
		
		if (enemies[i]->model->location.y > 600 || enemies[i]->health <= 0) {

			//Detach Child From Render Node
			enemyNode.detachChild(*enemies[i]->model);
			//Delete because tanks put on heap
			delete enemies[i]->model;
			delete enemies[i]->behavior;
			delete enemies[i];
			//Remove Tank from List
			enemies[i] = enemies[enemyCount-1];
			enemyCount--;

		}

	}

}

//Called on Loop
void EnemyManager::update() {

	move();

}

