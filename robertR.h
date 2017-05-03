//Basic 3f Vector
struct Vec {
	float x, y, z;
	Vec() {x=0;y=0;z=0;}
	Vec(float x, float y, float z) {this->x = x; this->y = y; this->z=z;};
};

//Abstract Spatial can be either Node or Spatial
class Node;
class Spatial {

	public:
		Spatial();
		Vec location;
		float angle;
		std::string name;
		Node *parent;
		Node getParent();

};

//Shape is a type of spatial that has an actual Geometry being drawn
class Shape: public Spatial {

	public:
		float width, height;
		float radius;
		Vec color;
		Shape();

};


//A Node is a Spatial that holds other Spatials
class Node: public Spatial {

	public:
		Node();
		Node  *nodeArr[15];
		Shape *shapeArr[15];
		int  shapeCount;
		int  nodeCount;
		void attachChild(Shape &s);
		void attachChild(Node  &n);
		void detachChild(Node &n);
		void detachChild(Shape &s); 
		bool hasChild(Node &n);
		bool hasChild(Shape &s);   
		void printTree();

};

//Abstract Structure with a single function
struct Behavior {
	virtual void behave(Node &model) = 0;
	virtual ~Behavior(){};
};


struct Bullet {
	Shape body;
	char  dir;
	char  source;
};

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

struct CarFriend {
	Behavior* behavior;
	Node*	  model;
	CarFriend(Node& n, Behavior& b);
	int health;
};

struct CarBehavior : public Behavior {

	bool isLeft;
	CarBehavior(bool left);
	void behave(Node &model);

};

class InteractionManager {

	public:
		void update(Display *dpy);
		void check_mouse(XEvent *e);
		void check_keys(XEvent *e);
		bool leftClick, rightClick, esc, up, down, left, right, space, enter;
		Vec  cursorLocation;

};

#include "bijanM.h"
#include "obosaO.h"
#include "jamesK.h"

class EntityManager {

	public:
		PlayerManager   pm;
		EnemyManager    em;
		FriendlyManager fm;
		EntityManager(InteractionManager &i);
		void update();
		void updateBullets();
		void checkCollision();
		bool collides(Shape s1, Shape s2);

};

struct Game {

	Node			   rootNode;
	InteractionManager im;
	EntityManager	   entm;
	Hud hud;
	Game();
	void printDataTree();

};

//Class Declaration
class GlUtils {

	private:
		Window win;
		GLXContext glc;
		void set_title(void);
		void renderNode(Node *node);
		void drawBullets();
		void drawBox(Shape box);
	
	public:
		void    initXWindows(void);
		void    init_opengl(void);
		void    cleanupXWindows(void);
		void    render(Game *game);
		void 	render(Game &game);
		Display *dpy;

};

