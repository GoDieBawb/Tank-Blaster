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

};

//Constructor passes InteractionManager to PlayerManager
EntityManager::EntityManager(InteractionManager &i) : pm(i) {
}

//Update Loop
void EntityManager::update() {
	pm.update();
	em.update();
	fm.update();
}
