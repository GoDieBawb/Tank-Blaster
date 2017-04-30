//#include "entity/unit/Tank/Tank.cpp"

struct Player {

	Tank tank;
	void initTank();
	Player();
    int score;
    int health;
    int carsLeft;
	bool isDead;
};

//Player constructor calls tank constructor with center screen vector
Player::Player() : tank(Vec(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,0)) {
	health = 3;
	carsLeft = 3;
	score = 0;
	isDead = true;
}


void Player::initTank() {
	tank.moveSpeed = 1;
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

Rect boxToRect(Shape &s);

class Hud {

	private:
		Shape bar;
		Shape textShape;
        Shape promptShape;
        Shape promptText;
		Node  hudNode;
		Tank  lifeDisplay;
		Tank  lifeDisplay2;
		Tank  lifeDisplay3;
        Car   car1;
        Car   car2;
        Car   car3;
        void checkForRestart();
        void prompt();
	public:
		Hud(Node &rootNode);
		void writeTestText();
		void update();
		void checkGameState();
	    void checkCarCount();
	    void checkPlayerHealth();

};
