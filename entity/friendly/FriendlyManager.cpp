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

//Constructor initializes data memebrs
FriendlyManager::FriendlyManager() {

	carCount 	 = 0;
	carNode.name = "Car Node";
	lastCar		 = time(0);
	initRoad();

}

void FriendlyManager::initRoad() {

	Shape *asphault = new Shape();

	asphault->height = WINDOW_HEIGHT*.15;
	asphault->width  = WINDOW_WIDTH;

	streetNode.location.y = WINDOW_HEIGHT - asphault->height/2 - WINDOW_HEIGHT/10;
	streetNode.location.x = WINDOW_WIDTH  - asphault->width/2;

	streetNode.attachChild(*asphault);
	asphault->color = Vec(111,110,99);

	for (int i = 0; i < 10; i++) {

		Shape *stripe 	   = new Shape();
		stripe->color      = yellow;
		stripe->height     = asphault->height/20;
		stripe->width      = asphault->width/15;
		stripe->location.y = 0;
		stripe->location.x = (-asphault->width/2) + (asphault->width/20) + ( (asphault->width/10)*i);
		streetNode.attachChild(*stripe);
	
	}

	//streetNode.printTree();

}

void FriendlyManager::move() {


	//Act on list of cars
	for (int i = 0; i < carCount; i++) {

		cars[i]->behavior->behave(*cars[i]->model);
		float xDist = cars[i]->model->location.x;
		if (xDist < 0) xDist *= -1;

		if (xDist > WINDOW_WIDTH+30 || cars[i]->health <= 0) {

			//std::cout << "Removing Car" << std::endl;
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

void FriendlyManager::carCreateCheck() {

	if (time(0) - lastCar < 2) return;

	//Create a car if not enough
	if (carCount < 10) {
		lastCar = time(0);

		bool skip = 0 + (rand() % (int) (1 - 0 + 1));

		if (skip)
			return;

		bool left = 0 + (rand() % (int) (1 - 0 + 1));

		int x;
		int y;
		//Randomize location
		if (left) {
			x = WINDOW_WIDTH;
			y = WINDOW_HEIGHT*.87;
		}
		
		else {
			x = 0;
			y = WINDOW_HEIGHT*.78;
		}

		//Local Variable put on heap
		Car* 		  c = new Car(Vec(x,y,0));
		CarBehavior*  b = new CarBehavior(left);
		CarFriend* 	  f = new CarFriend(*c,*b);

		int t = 1 + (rand() % (int) (3 - 1 + 3));
		Vec color;
		switch(t) {
			case (1): color = red; break;
			case (2): color = yellow; break;
			case (3): color = green; break;
			case (4): color = blue; break;
			default:  color = pink;
		}
		c->body.color  = color;
		c->front.color = color;
		c->back.color = color;

		//Add to list and render node
		cars[carCount] = f;
		carNode.attachChild(*c);
		carCount++;

	}

}

//Called on Loop
void FriendlyManager::update() {

	carCreateCheck();
	move();

}
