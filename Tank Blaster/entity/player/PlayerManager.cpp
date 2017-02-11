#include "../unit/Tank.cpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Player {

	Tank tank;
	void initTank();
	Player();

};

Player::Player() : tank(Vec(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0)) {

}

class PlayerManager {

	private:
		InteractionManager im;
		void actOnKeys();

	public:
		Player player;
		Node playerNode;
		PlayerManager(InteractionManager &i);
		Player getPlayer();
		void update();

};

PlayerManager::PlayerManager(InteractionManager &i) {

	playerNode.name = "Player Node";
	playerNode.attachChild(player.tank);
	im = i;

}

void PlayerManager::actOnKeys() {

	Tank* tank = &player.tank;

	if (im.up && im.left) {
		tank->moveUpLeft();
	}

	else if (im.up && im.right) {
		tank->moveUpRight();
	}


	else if (im.up) {
		tank->moveUp();
	}

	else if (im.down && im.left) {
		tank->moveDownLeft();
	}

	else if (im.down && im.right) {
		tank->moveDownRight();
	}

	else if (im.down) {
		tank->moveDown();
	}

	else if (im.left) {
		tank->moveLeft();
	}

	else if (im.right) {
		tank->moveRight();
	}
/*
	if (im.space) {
		game.bullets[game.bulletCount] = tank->shoot();
		game.bulletCount++;
		im.space = false;
	}
*/
}

void PlayerManager::update() {
	actOnKeys();
}
