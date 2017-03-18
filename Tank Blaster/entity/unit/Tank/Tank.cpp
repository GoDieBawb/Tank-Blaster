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

//Tanks without starting points are not tanks
Tank::Tank(){}

//Construct Tanks with a starting point
Tank::Tank(Vec loc) {

	//set up color vectors
	Vec black(0,0,0);
	Vec gray(50,50,50);
	Vec lightgray(80,80,80);
	Vec green(90,140,90);

	//Body Dimensions
	body.width     = 24;
	body.height    = 16;

	//Body is the tank body
	body.location  = Vec(0,0,0);

	//turret dimensions
	turret.width   = 14;
	turret.height  = 10;

	//set turret color
	turret.color   = lightgray;

	turret.location = Vec(0,0,0);
	
	//Set body color
	body.color     = green;

	//set right wheel dimensions
	rw.width       = 18;
	rw.height      = 4;

	//set left wheel dimensions	
	lw.width       = 18;
	lw.height      = 4;

	//set wheel color
	lw.color       = gray;
	rw.color       = gray;
	
	//wheels are at (12,0) from 
	//center of tank
	lw.location    = Vec(0,-9,0);
	rw.location    = Vec(0, 9,0);

	//Set Hatch Dimensions
	hatch.width    = 6;
	hatch.height   = 6;

	//Hatch is at CENTER OF TANK
	hatch.location = Vec(0,0,0);

	//Set Hatch Color
	hatch.color    = green;

	//Set Gun Dimensions
	gun.width      = 14;
	gun.height     = 3;

	//Gun is located at (0,12) from
	//Center of Tank
	gun.location   = Vec(12,0,0);
	
	//Set gun color
	gun.color      = black;

	//Set Names of Tank
	body.name  = "Body";
	hatch.name = "Hatch";
	gun.name   = "Gun";
	turret.name = "Turret";
	lw.name    = "LWheel";
	rw.name    = "RWheel";
	name 	   = "Tank";

	//ATTACH CHILDREN TO TANK
	attachChild(lw);
	attachChild(rw);

	attachChild(body);
	attachChild(turret);
	attachChild(hatch);
	attachChild(gun);

	//Tank starts facing upward
	angle		   =   0;
	dir	           = 'r';
	location 	   = loc;

	moveSpeed = 1.15/osDiv;

}

//This is not used at the moment
Bullet Tank::shoot() {

	//std::cout << "Shoot\n";
	Bullet b;
	Vec    spot;
	b.body.width  = 5;
	b.body.height = 5;
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

		case 'q':
			spot.x = -12/(sqrt(2)/2);	
			spot.y =  12/(sqrt(2)/2);
			break;
		case 'p':
			spot.x =  12/(sqrt(2)/2);	
			spot.y =  12/(sqrt(2)/2);
			break;
		case 'z':
			spot.x = -12/(sqrt(2)/2);	
			spot.y = -12/(sqrt(2)/2);
			break;
		case 'm':
			spot.x =   12/ (sqrt(2)/2);	
			spot.y =  -12/(sqrt(2)/2);
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
	location.y   += moveSpeed*tpf;
	//Set angle and direction
	dir 		  = 'u';
	angle		  =  90;
}

void Tank::moveDown() {
	//Subtract y if moving up
	location.y   -= moveSpeed*tpf;
	//Set angle and direction
	dir 		  = 'd';
	angle		  =  270;
}

void Tank::moveLeft() {
	//Subtract x if moving left
	location.x     -= moveSpeed*tpf;
	//Set angle and direction
	dir 		    = 'l';
	angle		    =  180;
}

void Tank::moveRight() {
	//Add x if moving right
	location.x   += moveSpeed*tpf;
	//Set angle and direction
	dir 		  = 'r';
	angle		  =   0;
}

void Tank::moveUpRight() {
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += moveSpeed/2*tpf;
	location.x   += moveSpeed/2*tpf;
	//Set angle and direction
	dir 		  = 'p';
	angle		  = 45;
}
void Tank::moveUpLeft() {
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += moveSpeed/2*tpf;
	location.x   -= moveSpeed/2*tpf;
	//Set angle and direction
	dir 		  = 'q';
	angle		  =  135;
}
void Tank::moveDownRight() {
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= moveSpeed/2*tpf;
	location.x   += moveSpeed/2*tpf;
	//Set angle and direction
	dir 		  = 'm';
	angle		  =  315;
}
void Tank::moveDownLeft() {
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= moveSpeed/2*tpf;
	location.x   -= moveSpeed/2*tpf;
	//Set angle and direction
	dir 		  =  'z';
	angle		  =  225;
}
