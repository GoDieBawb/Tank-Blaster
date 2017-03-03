
//This struct likely won't remain here
struct Bullet {

	Shape body;
	char  dir;

};

//Class Definition. Tank extends node
class Tank: public Node {

	private:
		char dir;

	public:
		Shape  body;
		Shape  hatch;
		Shape  gun;
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

//Tanks without starting points are not tanks
Tank::Tank(){}

//Construct Tanks with a starting point
Tank::Tank(Vec loc) {

	//Intialize Body

	//Body Dimensions
	body.width 	   = 16;
	body.height    = 16;

	//Body is at center of TANK<<
	body.location.x  = 0;
	body.location.y  = 0;

	//Set color
	body.color.x   = 90;
	body.color.y   = 140;
	body.color.z   = 90;

	//Set Hatch Dimensions
	hatch.width    = 2;
	hatch.height   = 2;

	//Hatch is at CENTER OF TANK
	hatch.location.x = 0;
	hatch.location.y = 0;

	//Set Hatch Color
	hatch.color.x  = 50;
	hatch.color.y  = 50;
	hatch.color.z  = 50;

	//Set Gun Dimensions
	gun.width 	     = 12;
	gun.height       = 2;

	//Gun is located at (0,12) from
	//Center of Tank
	gun.location.x   = 12;
	gun.location.y   = 0;

	//Set gun color
	gun.color.x    = 50;
	gun.color.y    = 50;
	gun.color.z    = 50;

	//Set Names of Tank
	body.name  = "Body";
	hatch.name = "Hatch";
	gun.name   = "Gun";
	name 	   = "Tank";

	//ATTACH CHILDREN TO TANK
	attachChild(body);
	attachChild(hatch);
	attachChild(gun);

	//Tank starts facing upward
	angle		   =   0;
	dir			   = 'r';
	location 	   = loc;

}

//This is not used at the moment
Bullet Tank::shoot() {

	std::cout << "Shoot\n";
	Bullet b;
	Vec    spot;
	b.body.width  = 2;
	b.body.height = 2;
	b.dir		  = dir;

	switch(dir) {
		
		case 'u':
			spot.x =  0;	
			spot.y = 12;
			break;
		case 'd':
			spot.x =   0;	
			spot.y = -12;
			break;
		case 'l':
			spot.x = -12;	
			spot.y =   0;
			break;
		case 'r':
			spot.x =  12;	
			spot.y =   0;
			break;

	}

	spot.x 		 += location.x;
	spot.y 		 += location.y;
	b.body.location = spot;
	
	return b;

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
	location.y   += .02*tpf;
	//Set angle and direction
	dir 		  = 'u';
	angle		  =  90;
}

void Tank::moveDown() {
	//Subtract y if moving up
	location.y   -= .02*tpf;
	//Set angle and direction
	dir 		  = 'd';
	angle		  =  270;
}

void Tank::moveLeft() {
	//Subtract x if moving left
	location.x     -= .02*tpf;
	//Set angle and direction
	dir 		    = 'l';
	angle		    =  180;
}

void Tank::moveRight() {
	//Add x if moving right
	location.x   += .02*tpf;
	//Set angle and direction
	dir 		  = 'r';
	angle		  =   0;
}

void Tank::moveUpRight() {
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .02/2*tpf;
	location.x   += .02/2*tpf;
	//Set angle and direction
	dir 		  = 'p';
	angle		  = 45;
}
void Tank::moveUpLeft() {
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .02/2*tpf;
	location.x   -= .02/2*tpf;
	//Set angle and direction
	dir 		  = 'q';
	angle		  =  135;
}
void Tank::moveDownRight() {
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .02/2*tpf;
	location.x   += .02/2*tpf;
	//Set angle and direction
	dir 		  = 'm';
	angle		  =  315;
}
void Tank::moveDownLeft() {
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .02/2*tpf;
	location.x   -= .02/2*tpf;
	//Set angle and direction
	dir 		  =  'z';
	angle		  =  225;
}
