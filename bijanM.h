//Enemy Manager will handle enemies and enemy behavior
class FriendlyManager {

	private:
		time_t 	   lastCar; //Time for last act	
		void   	   move();
		void   	   initRoad();

	public:
		int  carCount;
		void carCreateCheck();
		void update();
		Node carNode;
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
