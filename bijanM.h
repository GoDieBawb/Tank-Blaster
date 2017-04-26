//Enemy Manager will handle enemies and enemy behavior
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
    int minimum, maximum;
    bool goingup, init;
    void behave(Node &model);
};

class FriendlyManager {

	private:
		time_t 	   	lastCar; //Time for last act	
		void		maketowers();
		void		moveCars();
		void		initRoad();

	public:
		int  carCount;
		void carCreateCheck();
		void update();
		Node carNode;
		Tower leftTower, rightTower;
		TowerBehavior left, right;
		Node streetNode;
		FriendlyManager();
		CarFriend* cars[10];

};

//Class Definition. Tank extends node
class Tank: public Node {

	private:
		char dir;

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
