//Class Definition. Car extends node
class Car: public Node {

	private:
		char dir;

	public:
		Shape body,front,back,window,w1,w2,w3,w4;
		Car(Vec loc);
		void   moveRight();
		void   moveLeft();
		void   moveUp();
		void   moveDown();
		void   moveUpLeft();
		void   moveUpRight();
		void   moveDownLeft();
		void   moveDownRight();

};

Car::Car(Vec loc) {

	Vec black(0,0,0);
	Vec red(255,0,0);
	Vec gray(50,50,50);
	Vec blue(135,205,250);

	body.height=10;
	body.width=20;
	body.color = red;

	front.height = 9;
	front.width = 8;
	front.color = red;

	back.height = 9;
	back.width = 4;
	back.color = red;

	w1.height=6;
	w1.width=6;
	w1.color=black;

	w2.height = 6;
	w2.width  = 6;
	w2.color  =black;

	w3.height = 6;
	w3.width  = 6;
	w3.color  = black;

	w4.height = 6;
	w4.width  = 6;
	w4.color  = black;

	window.color  = blue;
	window.height = 10;
	window.width  = 5;

	body.location   = Vec(0,0,0);
	front.location	= Vec(10,0,0);
	back.location   = Vec(-10,0,0);
	w1.location		= Vec(9,6,0);
	w2.location		= Vec(9,-6,0);
	w3.location		= Vec(-9,6,0);
	w4.location		= Vec(-9,-6,0);
	window.location = Vec(7,0,0);

	body.name   = "Body";
	front.name  = "Front";
	back.name   = "Back";
	window.name = "Window";
	w1.name = "w1";
	w2.name = "w2";
	w3.name = "w3";
	w4.name = "w4";
	name 	= "Car";

	attachChild(w1);
	attachChild(w2);
	attachChild(w3);
	attachChild(w4);

	attachChild(body);
	attachChild(front);
	attachChild(back);
	attachChild(window);
	attachChild(back);

	angle 	 = 0;
	location = loc;

}

//Directions are a char
//u d l r
//p q z m
//p q z m represent diagnals
//I chose these because they
//are the corner of the 
//keyboard

//The Following Functions
//are used by the player
//as well as the Car
//behaviors

void Car::moveUp() {
	//Add to y if moving up
	location.y   += .05;
	//Set angle and direction
	dir 		  = 'u';
	angle		  =  90;
}

void Car::moveDown() {
	//Subtract y if moving up
	location.y   -= .05;
	//Set angle and direction
	dir 		  = 'd';
	angle		  =  270;
}

void Car::moveLeft() {
	//Subtract x if moving left
	location.x     -= .05;
	//Set angle and direction
	dir 		    = 'l';
	angle		    =  180;
}

void Car::moveRight() {
	//Add x if moving right
	location.x   += .05;
	//Set angle and direction
	dir 		  = 'r';
	angle		  =   0;
}

void Car::moveUpRight() {
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .05/2;
	location.x   += .05/2;
	//Set angle and direction
	dir 		  = 'p';
	angle		  = 45;
}
void Car::moveUpLeft() {
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .05/2;
	location.x   -= .05/2;
	//Set angle and direction
	dir 		  = 'q';
	angle		  =  135;
}
void Car::moveDownRight() {
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .05/2;
	location.x   += .05/2;
	//Set angle and direction
	dir 		  = 'm';
	angle		  =  315;
}
void Car::moveDownLeft() {
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .05/2;
	location.x   -= .05/2;
	//Set angle and direction
	dir 		  =  'z';
	angle		  =  225;
}

struct CarFriend {
	Behavior* behavior;
	Node*	  model;
	CarFriend(Node& n, Behavior& b);
	int health;
};

CarFriend::CarFriend(Node& n, Behavior& b) {
	model 	 = &n;
	behavior = &b;
	health   = 2;
}

struct CarBehavior : public Behavior {

	bool isLeft;
	CarBehavior(bool left);
	void behave(Node &model);

};

CarBehavior::CarBehavior(bool left) {
	isLeft = left;
}

void CarBehavior::behave(Node &model) {  

	Car &car = (Car&) model;

	if (isLeft)
		car.moveLeft();
	else
		car.moveRight();
				
}
