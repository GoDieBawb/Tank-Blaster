#include "player/PlayerManager.cpp"
#include "enemy/EnemyManager.cpp"
#include "friendly/FriendlyManager.cpp"

class EntityManager {

	public:
		PlayerManager   pm;
		EnemyManager    em;
		FriendlyManager fm;
		EntityManager(InteractionManager &i);
		void update();
		void updateBullets();
		void checkCollision();
		bool collides(Shape s1, Shape s2);

};

//Constructor passes InteractionManager to PlayerManager
EntityManager:: EntityManager(InteractionManager &i) : pm(i) {
}

void EntityManager::updateBullets() {

	for (int i = 0; i < bulletCount; i++) {

		Bullet* cur = &bullets[i];
		char   dir = cur->dir;

		switch (dir) {
			
		case 'u':
			cur->body.location.y += .25;
			break;
		case 'd':
			cur->body.location.y -= .25;
			break;
		case 'l':
			cur->body.location.x -= .25;
			break;
		case 'r':
			cur->body.location.x += .25;
			break;
		case 'q':
			cur->body.location.x -= .25/2;
			cur->body.location.y += .25/2;
			break;
		case 'p':
			cur->body.location.x += .25/2;
			cur->body.location.y += .25/2;
			break;
		case 'z':
			cur->body.location.x -= .25/2;
			cur->body.location.y -= .25/2;
			break;
		case 'm':
			cur->body.location.x += .25/2;
			cur->body.location.y -= .25/2;
			break;

		}

		int x = cur->body.location.x;
		int y = cur->body.location.y;

		if (x > WINDOW_WIDTH || x < 0) {
			bullets[i] = bullets[bulletCount-1];
			bulletCount--;
		}

		else if (y > WINDOW_HEIGHT || y < 0 ) {
			bullets[i] = bullets[bulletCount-1];
			bulletCount--;
		}

	}
	
}

void EntityManager::checkCollision() {

	for (int i = 0; i < bulletCount; i++) {

		Shape* cur = &bullets[i].body;

		for (int j = 0; j < em.enemyCount; j++) {

			Node* ce = em.enemyNode.nodeArr[j];

			for (int k = 0; k < ce->shapeCount; k++) {

				Shape s = *ce->shapeArr[k];
				s.location.x += ce->location.x;
				s.location.y += ce->location.y;

				if (collides(s,*cur)) {
					Enemy *enemy = em.enemies[j];
					enemy->health--;
					bullets[i] = bullets[bulletCount-i];
					bulletCount--;
				}				
				
			}

		}
	
	}

}

bool EntityManager::collides(Shape s1, Shape s2) {

	int x1 = s1.location.x;
	int x2 = s2.location.x;

	int y1 = s1.location.y;
	int y2 = s2.location.y;

	//printf("[%d,%d] [%d,%d]\n", x1,y1,x2,y2);

	int l1 = x1 - s1.width/2;
	int r1 = x1 + s1.width/2;

	int l2 = x2 - s2.width/2;
	int r2 = x2 + s2.width/2;

	int t1 = y1 + s1.height/2;
	int b1 = y1 - s1.height/2;

	int t2 = y2 + s2.height/2;
	int b2 = y2 - s2.height/2;

	int count = 0;;

	if 		(l1 > l2 && l1 < r2) {count++;}
	else if (r1 < l2 && r1 > r2) {count++;}

	if 		(t1 < t2 && t1 > b2) {count++;}
	else if (b1 > b2 && b1 < t2) {count++;}

	if (count != 2) return false;

	return true;

}

//Update Loop
void EntityManager::update() {
	updateBullets();
	checkCollision();
	pm.update();
	em.update();
	fm.update();
}
