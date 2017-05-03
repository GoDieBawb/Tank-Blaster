//Name: Bijan Mirkazemi
//Description: individual file for Software engineering game
//Course: cmps 3350 Software Engineering
//
//
//Functionality: 
//--FriendlyManager manages the friendly entities such as cars, towers.
//--creation of the road and the movement of the cars at top of screen
//--Tower constructor creates a tower
//--Tank constructor creates a tank
//--TowerBehavior makes the gun on the tower rotate
//
//--Friendly entities are blue or yellow, enemies are red. 
//
//
//TO DO STILL: UPDATED 5/1
//
//

FriendlyManager::FriendlyManager() : 
	leftTower(Vec(50,400,0)), rightTower(Vec(750,400,0)), 
	left(-30,30), right(150,210) {

	carCount = 0;
	carNode.name = "Car Node";
	lastCar	= time(0);
	initRoad();
}

void FriendlyManager::initRoad() 
{
	Shape *asphault = new Shape();
	asphault->height = WINDOW_HEIGHT*.15;
	asphault->width = WINDOW_WIDTH;
	streetNode.location.y = WINDOW_HEIGHT 
							- asphault->height/2 - WINDOW_HEIGHT/10;
	streetNode.location.x = WINDOW_WIDTH - asphault->width/2;
	streetNode.attachChild(*asphault);
	asphault->color = Vec(111,110,99);
	for (int i = 0; i < 10; i++) {
		Shape *stripe = new Shape();
		stripe->color = yellow;
		stripe->height = asphault->height/20;
		stripe->width = asphault->width/15;
		stripe->location.y = 0;
		stripe->location.x = (-asphault->width/2) 
							+ (asphault->width/20) + ( (asphault->width/10)*i);
		streetNode.attachChild(*stripe);
	}
}

void FriendlyManager::moveCars() 
{
	//Act on Civilian Cars...
	for (int i = 0; i < carCount; i++) {
		cars[i]->behavior->behave(*cars[i]->model);
		float xDist = cars[i]->model->location.x;
		if (xDist < 0) {
			xDist *= -1;
		}
		if (xDist > WINDOW_WIDTH+30 || cars[i]->health <= 0) {
			if (cars[i]->health <= 0) {
				game.entm.pm.player.carsLeft--;
				doExplosion();
			}
			//Detach Child From Render Node
			carNode.detachChild(*cars[i]->model);
			//Delete because tanks put on heap
			delete cars[i]->model;
			delete cars[i]->behavior;
			delete cars[i];
			//Remove Car from List
			cars[i] = cars[carCount-1];
			carCount--;
		}
	}
}

void FriendlyManager::carCreateCheck() 
{
	if (time(0) - lastCar < 2) {
		return;
	}
	//Create a car if necessary
	if (carCount < 20) {
		lastCar = time(0);
		bool skip = (rand() % (int)(1-0+1));
		if (skip) {
			return;
		}
		bool leftlane = (rand() % (int)(1-0+1));
		int x;
		int y;
		//Randomize location
		if (leftlane) {
			x = WINDOW_WIDTH;
			y = WINDOW_HEIGHT*.87;
		} else {
			x = 0;
			y = WINDOW_HEIGHT*.78;
		}
		//Local Variable put on heap
		Car* car = new Car(Vec(x,y,0));
		CarBehavior* behavior = new CarBehavior(leftlane);
		CarFriend* friendly = new CarFriend(*car,*behavior);
		int t = 1 + (rand() % (int)(3-1+3));
		Vec color;
		switch(t) {
			case (1): 
				color = red; 
				break;
			case (2): 
				color = yellow; 
				break;
			case (3): 
				color = green; 
				break;
			case (4): 
				color = blue; 
				break;
			default: 
				color = pink;
		}
		car->body.color = color;
		car->front.color = color;
		car->back.color = color;
		//Add to list and render node
		cars[carCount] = friendly;
		carNode.attachChild(*car);
		carCount++;
	}
}

//Called on Loop
void FriendlyManager::update() 
{
	carCreateCheck();
	moveCars();
	left.behave(leftTower);	
	right.behave(rightTower);
}

Tower::Tower(Vec loc) {   
    Vec black(0,0,0);
    Vec lightgray(70,70,70);
    Vec gray(50,50,50);
    Vec green(90,140,90);
	Vec lightblue(31,127,196);

    body.height = 40;
	body.width = 40;
	body.color = lightgray;
    
    roof.height = 20;
    roof.width = 20;
    roof.color = yellow;

    gun.color = black;
    gun.width = 18;
    gun.height = 4;

    gunbase.color = black;
    gunbase.width = 8;
    gunbase.height = 8;

	c1.color = lightgray;
	c1.width = 6;
	c1.height = 6;
    
	c2.color = lightgray;
	c2.width = 6;
	c2.height = 6;
    
	c3.color = lightgray;
	c3.width = 6;
	c3.height = 6;

	c4.color = lightgray;
	c4.width = 6;
	c4.height = 6;

	body.location = Vec(0,0,0);
	c1.location = Vec(14,18,0);    
	c2.location = Vec(14,-18,0);    
	c3.location = Vec(-14,18,0);    
	c4.location = Vec(-14,-18,0);    
	roof.location = Vec(0,0,0);
    gun.location = Vec(10,0,0);
    gunbase.location = Vec(0,0,0);

    body.name = "Body";
	c1.name = "Corner 1";
	c2.name = "Corner 2";
	c3.name = "Corner 3";
	c4.name = "Corner 4";
    roof.name = "Roof";
    gun.name = "Gun";
    gunbase.name = "Gun Base";
    name = "Tower";

    attachChild(body);
	attachChild(c1);
	attachChild(c2);
	attachChild(c3);
	attachChild(c4);
    attachChild(roof);
    attachChild(gun);
    attachChild(gunbase);

    angle = 0;
    location = loc;
}

TowerBehavior::TowerBehavior(int min, int max) {
	goingup 	= false;
	init 		= false;
	shooting 	= false;
	maximum 	= max; 
	minimum 	= min;
	lastShot 	= clock();
	burstDelay 	= clock();
	burstCount 	= 0;
}

void TowerBehavior::shoot(Vec loc) 
{
	Bullet b;
	b.body.width  = 5;
	b.body.height = 5;
	int angle = (maximum + minimum)/2;
	if (angle < 0) angle*=-1;
	if (angle == 0) {
		b.dir = 'r';
		b.body.location.x = loc.x + 12;
		b.body.location.y = loc.y;
	} else {
		b.dir = 'l';
		b.body.location.x = loc.x - 12;
		b.body.location.y = loc.y;
	}
	bullets[bulletCount] = b;
	bulletCount++;
}

void TowerBehavior::behave(Node &model) 
{
	Tower &tower = (Tower&) model;
	if (!init) {
		tower.gun.angle = minimum + 1;
		init = true;
	}
	float shootAngle = (maximum + minimum) / 2;
	time_t t = clock() - lastShot;
	double delay = ((float)(t)) / CLOCKS_PER_SEC*10;
	if (delay > 6 && !shooting) {
		float currentAngle = tower.gun.angle - shootAngle;
		if (currentAngle < 0) {
			currentAngle *= -1;
		}
		if (currentAngle < .1) {
			shooting = true;
			lastShot = clock();	
		}
	}
	if (shooting) {
		time_t t = clock() - burstDelay;
		double bDelay = ((float)t)/CLOCKS_PER_SEC*10;
		if (bDelay > .25) {
			burstDelay = clock();
			shoot(tower.location);
			burstCount++;
		}
		if (burstCount == 3) {
			shooting   = false;
			burstCount = 0;		
		}
	} else if (goingup) { 
		tower.gun.angle += 0.5;
	} else {
		tower.gun.angle -= 0.5;
	}
	if (tower.gun.angle > maximum || tower.gun.angle < minimum) {
		goingup = !goingup;
	}
}

//Tanks without starting points are not tanks
Tank::Tank() {}

//Construct Tanks with a starting point
Tank::Tank(Vec loc) {
	Vec black(0,0,0);
	Vec gray(50,50,50);
	Vec lightgray(80,80,80);
	Vec green(90,140,90);
	Vec lightblue(31,127,196);

	body.width = 24;
	body.height = 16;
	body.color = lightblue;

	turret.width = 14;
	turret.height = 10;
	turret.color = lightgray;

	rw.width = 28;
	rw.height = 4;
	rw.color = gray;

	lw.width = 28;
	lw.height = 4;
	lw.color = gray;

	hatch.width = 6;
	hatch.height = 6;
	hatch.color = green;

	gun.width = 14;
	gun.height = 3;
	gun.color = black;
	
	body.location = Vec(0,0,0);
	turret.location = Vec(0,0,0);
	lw.location = Vec(0,-9,0);
	rw.location = Vec(0, 9,0);
	hatch.location = Vec(0,0,0);
	gun.location = Vec(12,0,0);

	body.name = "Body";
	hatch.name = "Hatch";
	gun.name = "Gun";
	turret.name = "Turret";
	lw.name = "Left Wheel";
	rw.name = "Right Wheel";
	name = "Tank";

	attachChild(lw);
	attachChild(rw);
	attachChild(body);
	attachChild(turret);
	attachChild(hatch);
	attachChild(gun);
	
	angle = 90;
	dir	  = 'u';
	location  = loc;
	moveSpeed = .25;
	lastShot  = clock();
}

Bullet Tank::shoot() {

	time_t t     = clock() - lastShot;
	double delay = ((float)t)/CLOCKS_PER_SEC*10;

	if (delay < .1) {
		bulletCount--;
		return bullets[bulletCount];
	}

	lastShot = clock();

	Bullet bullet;
	Vec spot;
	bullet.body.name  = "b";
	bullet.body.angle = 0; 
	bullet.body.width  = 5;
	bullet.body.height = 5;
	bullet.dir = dir;

	switch(dir) {		
		case 'u':
			spot.x =  0;	
			spot.y = 12*1.5;
			break;
		case 'd':
			spot.x =   0;	
			spot.y = -12*1.5;
			break;
		case 'l':
			spot.x = -12*1.5;	
			spot.y =   0;
			break;
		case 'r':
			spot.x =  25;	
			spot.y =   0;
			break;
		case 'q':
			spot.x = -12/(sqrt(2)/2)*1.5;	
			spot.y =  12/(sqrt(2)/2)*1.5;
			break;
		case 'p':
			spot.x =  12/(sqrt(2)/2)*1.5;	
			spot.y =  12/(sqrt(2)/2)*1.5;
			break;
		case 'z':
			spot.x = -12/(sqrt(2)/2)*1.5;	
			spot.y = -12/(sqrt(2)/2)*1.5;
			break;
		case 'm':
			spot.x =   12/ (sqrt(2)/2)*1.5;	
			spot.y =  -12/(sqrt(2)/2)*1.5;
			break;
	}
	spot.x += location.x;
	spot.y += location.y;
	bullet.body.location = spot;
	return bullet;
}

//Directions are a char
//u d l r
//p q z m
//p q z m represent diagnals
//This is because they
//are the corner of the keyboard

//The Following Functions
//are used by the player
//as well as the tank
//behaviors

void Tank::moveUp() 
{
	//Add to y if moving up
	location.y += moveSpeed;
	dir = 'u';
	angle = 90;
}

void Tank::moveDown() 
{
	//Subtract y if moving up
	location.y -= moveSpeed;
	dir = 'd';
	angle = 270;
}

void Tank::moveLeft() 
{
	//Subtract x if moving left
	location.x -= moveSpeed;
	dir = 'l';
	angle = 180;
}

void Tank::moveRight() 
{
	//Add x if moving right
	location.x += moveSpeed;
	dir = 'r';
	angle = 0;
}

void Tank::moveUpRight() 
{
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y += moveSpeed/2;
	location.x += moveSpeed/2;
	dir = 'p';
	angle = 45;
}

void Tank::moveUpLeft() 
{
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y += moveSpeed/2;
	location.x -= moveSpeed/2;
	//Set angle and direction
	dir = 'q';
	angle = 135;
}

void Tank::moveDownRight() 
{
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y -= moveSpeed/2;
	location.x += moveSpeed/2;
	dir = 'm';
	angle = 315;
}

void Tank::moveDownLeft() 
{
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y -= moveSpeed/2;
	location.x -= moveSpeed/2;
	dir = 'z';
	angle = 225;
}
