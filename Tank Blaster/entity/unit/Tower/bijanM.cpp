//Name: Bijan Mirkazemi
//Description: creating an enemy tower object
//Course


class Tower: public Node {
    private: 
	char dir;
    public:
	Shape tower, roof, gun;
	Tower();
	Tower(Vec loc);
}

public Tower(Vec loc) {
    Shape tower;
    Shape roof;
    Shape gun;

    Vec black(0,0,0);
    Vec gray(50,50,50);

    body.height = 40;
    body.width = 40;
    body.color = gray;
    
    roof.height = 18;
    roof.width = 18;
    roof.color = black;

    gun.color = black;
    gun.width = 8;
    gun.height = 2;

    body.location = Vec(0,0,0);
    roof.location = Vec(0,0,0);
    gun.location = Vec(0,0,0);

    tower.attachChild(body);
    tower.attachChild(roof);
    tower.attachChild(gun);

    tower.angle = 0;
    tower.location = Vec(100,100,0);
}
