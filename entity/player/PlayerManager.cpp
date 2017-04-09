#include "../unit/Tank/Tank.cpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Player {

	Tank tank;
	void initTank();
	Player();

};

//Player constructor calls tank constructor with center screen vector
Player::Player() : tank(Vec(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0)) {

}

void Player::initTank() {
	tank.moveSpeed = .05;
}

//Manages Player Actions and Behavior
class PlayerManager {

	private:
		InteractionManager* im;
		void actOnKeys();

	public:
		Player player;
		Node playerNode;
		PlayerManager(InteractionManager &i);
		Player getPlayer();
		void update();

};

//Constructor initializes data members
PlayerManager::PlayerManager(InteractionManager &i) {

	//Name Player Node
	playerNode.name = "Player Node";
	//Attach player tank to player node
	playerNode.attachChild(player.tank);
	//Set interaction manager
	im = &i;

}

//Uses InteractionManager to listen for key presses
void PlayerManager::actOnKeys() {

	Tank* tank = &player.tank;

	if (im->up && im->left) {
		tank->moveUpLeft();
	}

	else if (im->up && im->right) {
		tank->moveUpRight();
	}

	else if (im->up) {
		tank->moveUp();
	}

	else if (im->down && im->left) {
		tank->moveDownLeft();
	}

	else if (im->down && im->right) {
		tank->moveDownRight();
	}

	else if (im->down) {
		tank->moveDown();
	}

	else if (im->left) {
		tank->moveLeft();
	}

	else if (im->right) {
		tank->moveRight();
	}

	if (im->space) {
		bullets[bulletCount] = tank->shoot();
		bulletCount++;
		im->space = false;
	}

}

//Called on Update Loop
void PlayerManager::update() {
	actOnKeys();
}
