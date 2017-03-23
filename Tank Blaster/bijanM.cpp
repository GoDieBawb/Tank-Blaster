//Name: Bijan Mirkazemi
//Description: creating an enemy tower object
//Course: cmps 3350 Software Engineering

class Tower: public Node {
    private: 
	char dir;
    public:
	Shape body, roof, gun, gunbase;
	Tower();
	Tower(Vec loc);
};

Tower::Tower(Vec loc) {
    
    Vec black(0,0,0);
    Vec lightgray(70,70,70);
    Vec gray(50,50,50);
    Vec green(90,140,90);

    body.height = 40;
    body.width = 40;
    body.color = green;
    
    roof.height = 20;
    roof.width = 20;
    roof.color = lightgray;

    gun.color = black;
    gun.width = 18;
    gun.height = 4;

    gunbase.color = black;
    gunbase.width = 8;
    gunbase.height = 8;
    
    body.location = Vec(0,0,0);
    roof.location = Vec(0,0,0);
    gun.location = Vec(10,0,0);
    gunbase.location = Vec(0,0,0);


    body.name = "Body";
    roof.name = "Roof";
    gun.name = "Gun";
    gunbase.name = "Gun Base";
    name = "Tower";

    attachChild(body);
    attachChild(roof);
    attachChild(gun);
    attachChild(gunbase);


    angle = 0;
    location = loc;
}

struct TowerBehavior : public Behavior {
	TowerBehavior(int min, int max);
	int minimum, maximum;
	bool goingup, init;
	void behave(Node &model);
};

TowerBehavior::TowerBehavior(int min, int max) {
	goingup = false;
	init = false;
	maximum = max; 
	minimum = min;
}

void TowerBehavior::behave(Node &model) {

	Tower &tower = (Tower&) model;
	if(!init) {
		tower.gun.angle = minimum + 1;
	init = true;
	}
	if(goingup) 
		tower.gun.angle += 0.5;
	else 
		tower.gun.angle -= 0.5;
	if(tower.gun.angle > maximum || tower.gun.angle < minimum) 
		goingup = !goingup;
}

