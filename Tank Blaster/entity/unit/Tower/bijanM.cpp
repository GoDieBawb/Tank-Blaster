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

    tower.height = 40;
    tower.width = 40;
    tower.color = gray;
    
    roof.height = 18;
    roof.width = 18;
    roof.color = black;

    gun.color = black;
    gun.width = 8;
    gun.height = 2;
}
