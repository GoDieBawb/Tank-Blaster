#include "player/PlayerManager.cpp"

class EntityManager {

	private:
		void movement();

	public:
		PlayerManager pm;
		EntityManager(InteractionManager &i);
		void update();

};

EntityManager::EntityManager(InteractionManager &i) : pm(i) {
}

void EntityManager::movement() {

}

void EntityManager::update() {
	pm.update();
}
