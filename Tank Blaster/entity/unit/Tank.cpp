struct Bullet {

	Shape body;
	char  dir;

};

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

Tank::Tank(){}

Tank::Tank(Vec loc) {

	
	body.width 	   = 16;
	body.height    = 16;
	body.location.x  = 0;
	body.location.y  = 0;
	body.color.x   = 90;
	body.color.y   = 140;
	body.color.z   = 90;

	hatch.width    = 2;
	hatch.height   = 2;
	hatch.location.x = 0;
	hatch.location.y = 0;
	hatch.color.x  = 50;
	hatch.color.y  = 50;
	hatch.color.z  = 50;

	gun.width 	     = 12;
	gun.height       = 2;
	gun.location.x   = 0;
	gun.location.y   = 12;
	gun.color.x    = 50;
	gun.color.y    = 50;
	gun.color.z    = 50;

	body.name  = "Body";
	hatch.name = "Hatch";
	gun.name   = "Gun";
	name 	   = "Tank";


	attachChild(body);
	attachChild(hatch);
	attachChild(gun);

	angle		   = 90;
	dir			   = 'u';
	location 	   = loc;

}

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

void Tank::moveUp() {
	location.y   += .01;
	dir 		  = 'u';
	angle		  =  90;
}

void Tank::moveDown() {
	location.y   -= .01;
	dir 		  = 'd';
	angle		  =  270;
}

void Tank::moveLeft() {
	location.x     -= .01;
	dir 		    = 'l';
	angle		    =  180;
}

void Tank::moveRight() {
	location.x   += .01;
	dir 		  = 'r';
	angle		  =   0;
}

void Tank::moveUpRight() {
	location.y   += .01;
	location.x   += .01;
	dir 		  = 'p';
	angle		  = 45;
}
void Tank::moveUpLeft() {
	location.y   += .01;
	location.x   -= .01;
	dir 		  = 'q';
	angle		  =  135;
}
void Tank::moveDownRight() {
	location.y   -= .01;
	location.x   += .01;
	dir 		  = 'm';
	angle		  =  315;
}
void Tank::moveDownLeft() {
	location.y   -= .01;
	location.x   -= .01;
	dir 		  =  'z';
	angle		  =  225;
}
