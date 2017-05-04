//Friendly Manager will handle friendlies and friendly behavior
class Tower: public Node {
	private:
		char dir;
	public:
		Shape c1,c2,c3,c4;
		Shape body, roof, gun, gunbase;
		Tower();
		Tower(Vec loc);
};

struct TowerBehavior : public Behavior {
	TowerBehavior(int min, int max);
	TowerBehavior();
	int minimum, maximum, burstCount;
	bool goingup, init, shooting;
	time_t lastShot;
	time_t burstDelay;
	void behave(Node &model);
	void shoot(Vec loc);
};

class FriendlyManager {
	private:
		time_t lastCar; //Time for last act	
		void maketowers();
		void moveCars();
		void initRoad();
	public:
		int carCount;
		void carCreateCheck();
		void update();
		Node carNode;
		Tower leftTower; 
		Tower rightTower;
		TowerBehavior left;
		TowerBehavior right;
		Node streetNode;
		FriendlyManager();
		CarFriend* cars[20];
};

//Class Definition. Tank extends node
class Tank: public Node {
	private:
		char dir;
		time_t lastShot; //Time for last act
	public:
		Shape  body;
		Shape  hatch;
		Shape  turret;
		Shape  lw,rw;
		Shape  gun;
		float  moveSpeed;
		Tank();
		Tank(Vec loc);
		void   moveRight();
		void   moveLeft();
		void   moveUp();
		void   moveDown();
		void   moveUpLeft();
		void   moveUpRight();
		void   moveDownLeft();
		void   moveDownRight();
		Bullet shoot();

};
