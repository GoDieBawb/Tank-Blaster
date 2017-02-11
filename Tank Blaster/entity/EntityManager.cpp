#include "player/PlayerManager.cpp"
#include "enemy/EnemyManager.cpp"

class EntityManager {

	public:
		PlayerManager pm;
		EnemyManager  em;
		EntityManager(InteractionManager &i);
		void update();

};

//Constructor passes InteractionManager to PlayerManager
EntityManager::EntityManager(InteractionManager &i) : pm(i) {
}

//Update Loop
void EntityManager::update() {
	pm.update();
	em.update();
}
