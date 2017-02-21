//Class Definition. Tank extends node
class Jeep: public Node {

	private:
		char dir;

	public:
		Shape body,front,gun,window,w1,w2,w3,w4;
		Jeep();
		Jeep(Vec loc);
		void   moveRight();
		void   moveLeft();
		void   moveUp();
		void   moveDown();
		void   moveUpLeft();
		void   moveUpRight();
		void   moveDownLeft();
		void   moveDownRight();
		//Bullet shoot();

};

public Jeep(Vec loc) {

	Shape w1,w2,w3,w4;
	Shape body;
	Shape front;
	Shape window;
	Shape gun;

	Vec black(0,0,0);
	Vec green(90,140,90);
	Vec gray(50,50,50);
	Vec blue(135,205,250);

	body.height=12;
	body.width=24;
	body.color = green;

	front.height = 10;
	front.width = 6;
	front.color = green;

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
	
	gun.color  = gray;
	gun.height = 2;
	gun.width  = 8;

	window.color  = blue;
	window.height = 10;
	window.width  = 5;

	body.location   = Vec(0,0,0);
	front.location	= Vec(12,0,0);
	w1.location		= Vec(10,6,0);
	w2.location		= Vec(10,-6,0);
	w3.location		= Vec(-10,6,0);
	w4.location		= Vec(-10,-6,0);
	gun.location	= Vec(-6,0,0);
	window.location = Vec(10,0,0);

	jeep.attachChild(w1);
	jeep.attachChild(w2);
	jeep.attachChild(w3);
	jeep.attachChild(w4);

	jeep.attachChild(body);
	jeep.attachChild(front);
	jeep.attachChild(window);
	jeep.attachChild(gun);

	jeep.angle 	  = 180;
	jeep.location = Vec(400,400,0);

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
//as well as the tank
//behaviors

void Tank::moveUp() {
	//Add to y if moving up
	location.y   += .01;
	//Set angle and direction
	dir 		  = 'u';
	angle		  =  90;
}

void Tank::moveDown() {
	//Subtract y if moving up
	location.y   -= .01;
	//Set angle and direction
	dir 		  = 'd';
	angle		  =  270;
}

void Tank::moveLeft() {
	//Subtract x if moving left
	location.x     -= .01;
	//Set angle and direction
	dir 		    = 'l';
	angle		    =  180;
}

void Tank::moveRight() {
	//Add x if moving right
	location.x   += .01;
	//Set angle and direction
	dir 		  = 'r';
	angle		  =   0;
}

void Tank::moveUpRight() {
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .01/2;
	location.x   += .01/2;
	//Set angle and direction
	dir 		  = 'p';
	angle		  = 45;
}
void Tank::moveUpLeft() {
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .01/2;
	location.x   -= .01/2;
	//Set angle and direction
	dir 		  = 'q';
	angle		  =  135;
}
void Tank::moveDownRight() {
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .01/2;
	location.x   += .01/2;
	//Set angle and direction
	dir 		  = 'm';
	angle		  =  315;
}
void Tank::moveDownLeft() {
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .01/2;
	location.x   -= .01/2;
	//Set angle and direction
	dir 		  =  'z';
	angle		  =  225;
}
