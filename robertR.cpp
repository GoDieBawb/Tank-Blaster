void doExplosion(){}
void doMusic(){}
void doShoot(){}
void initSound(){}
void cleanUpSound(){}

//Sound stuff based on Gordon's Worm Framework Sound
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*
//Finally a straight forward OpenAL sample program.
//Gordon Griesel
//2016
//This demo plays two simultaneous sounds.
//One is looping, the other is not looping.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alut.h>
#include <pthread.h>

//Buffers hold the sound information.
ALuint alBuffer[2];
//Source refers to the sound.
ALuint alSource[2];

ALuint alBufferExplode, alBufferMusic, alBufferShoot;
ALuint alSourceExplode, alSourceMusic, alSourceShoot;

void initExplosion();
void initMusic();

void initSound() {

	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return;
	}
	//Clear error state.
	alGetError();
	//
	//Setup the listener.
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
	//
	//Buffer holds the sound information.
	alBufferExplode = alutCreateBufferFromFile("./Explode.wav");

	//Source refers to the sound.
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceExplode);
	alSourcei(alSourceExplode, AL_BUFFER, alBufferExplode);
	alSourcef(alSourceExplode, AL_GAIN, .5f);
	alSourcef(alSourceExplode, AL_PITCH, 1.0f);
	alSourcei(alSourceExplode, AL_LOOPING, AL_FALSE);

	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alBufferMusic   = alutCreateBufferFromFile("./Home_Base_Groove.wav");
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceMusic);
	alSourcei(alSourceMusic, AL_BUFFER, alBufferMusic);
	alSourcef(alSourceMusic, AL_GAIN, 5.0f);
	alSourcef(alSourceMusic, AL_PITCH, 1.0f);
	alSourcei(alSourceMusic, AL_LOOPING, AL_TRUE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alBufferShoot   = alutCreateBufferFromFile("./Shoot.wav");
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceShoot);
	alSourcei(alSourceShoot, AL_BUFFER, alBufferShoot);
	alSourcef(alSourceShoot, AL_GAIN, .1f);
	alSourcef(alSourceShoot, AL_PITCH, 1.0f);
	alSourcei(alSourceShoot, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

}


void cleanUpSound() {

	//First delete the source.
	alDeleteSources(1, &alSourceExplode);
	alDeleteSources(1, &alSourceMusic);
	alDeleteSources(1, &alSourceShoot);
	//Delete the buffer.
	alDeleteBuffers(1, &alBufferExplode);
	alDeleteBuffers(1, &alBufferMusic);
	alDeleteBuffers(1, &alBufferShoot);
	//Close out OpenAL itself.
	//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
	//Release context(s).
	alcDestroyContext(Context);
	//Close device.
	alcCloseDevice(Device);

}

void playSound(ALuint source){
	alSourcePlay(source);
}

void* runSong(void*) {
	playSound(alSourceExplode);
	pthread_exit(NULL);
}

void* runExplode(void*) {
	playSound(alSourceMusic);
	pthread_exit(NULL);
}

pthread_t soundThread[2];

void doMusic() {
	alSourcePlay(alSourceMusic);
	//alSourcePlay(alSource[1]);
	//pthread_create(&soundThread[0], NULL, runSong, NULL);
}

void doShoot() {
	//printf("EXPLODE\n");
	playSound(alSourceShoot);
	//alSourcePlay(alSource[0]);		
	//pthread_create(&soundThread[1], NULL, runExplosion, NULL);
}

void doExplosion() {
	//printf("EXPLODE\n");
	playSound(alSourceExplode);
	//alSourcePlay(alSource[0]);		
	//pthread_create(&soundThread[1], NULL, runExplosion, NULL);
}
*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/


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

Spatial::Spatial() {
	angle = 0;
}

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
		void printTree();

};

Shape::Shape() {
	name = "Shape";
}

//Construct Node
Node::Node() {
	name 	   = "Node";
	shapeCount = 0;
	nodeCount  = 0;
}

//Attach Shape to Node
void Node::attachChild(Shape &s) {
	shapeArr[shapeCount] = &s;
	shapeCount++;
	s.parent = this;
}

//Attach Node to Node
void Node::attachChild(Node &n) {
	nodeArr[nodeCount] = &n;
	nodeCount++;
	n.parent = this;
}

//Remove Shape Child from Node
void Node::detachChild(Shape &s) {

	for (int i =0; i < shapeCount; i++) {

		if (shapeArr[i] == &s) {
			shapeArr[i] = shapeArr[shapeCount];
			shapeCount--;
			return;
		}

	}

	std::cout << "CHILD NOT FOUND!\n";

}
 
//Remove Node Child From Node
void Node::detachChild(Node &n) {

	for (int i =0; i < nodeCount; i++) {

		if (nodeArr[i] == &n) {
			nodeArr[i] = nodeArr[nodeCount-1];
			nodeCount--;	
			return;
		}

	}

	std::cout << "CHILD NOT FOUND!\n";

}

//Recusrive Function to Print Nodes Children
void Node::printTree() {

	std::cout << name << "\n";

	for (int i = 0; i < shapeCount; i++) {
		std::cout << shapeArr[i]->name << " ";
	}

	for (int i = 0; i < nodeCount; i++) {
		nodeArr[i]->printTree();
	}

	std::cout << "\n";

}

//Particle
struct Particle {
	Shape s;
	Vec velocity;
};

/*------------------------------------------------------------------------------------------------------------------------------------------*/


//Abstract Structure with a single function
struct Behavior {
	virtual void behave(Node &model) = 0;
	virtual ~Behavior(){};
};

/*------------------------------------------------------------------------------------------------------------------------------------------*/


struct Bullet {
	Shape body;
	char  dir;
	char  source;
};
Bullet bullets[500];
int bulletCount = 0;

/*------------------------------------------------------------------------------------------------------------------------------------------*/


//Public Color Vector
Vec red    = Vec(255,0,0);
Vec green  = Vec(0,255,0);
Vec blue   = Vec(0,0,255);
Vec yellow = Vec(255,255,0);
Vec pink   = Vec(255,182,193);
Vec black  = Vec(0,0,0);

/*------------------------------------------------------------------------------------------------------------------------------------------*/


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

Car::Car(Vec loc) {

	Vec black(0,0,0);
	Vec red(255,0,0);
	Vec gray(50,50,50);
	Vec blue(135,205,250);

	body.height=10;
	body.width=20;
	body.color = red;

	front.height = 9;
	front.width = 8;
	front.color = red;

	back.height = 9;
	back.width = 4;
	back.color = red;

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

	window.color  = blue;
	window.height = 10;
	window.width  = 5;

	body.location   = Vec(0,0,0);
	front.location	= Vec(10,0,0);
	back.location   = Vec(-10,0,0);
	w1.location		= Vec(9,6,0);
	w2.location		= Vec(9,-6,0);
	w3.location		= Vec(-9,6,0);
	w4.location		= Vec(-9,-6,0);
	window.location = Vec(7,0,0);

	body.name   = "Body";
	front.name  = "Front";
	back.name   = "Back";
	window.name = "Window";
	w1.name = "w1";
	w2.name = "w2";
	w3.name = "w3";
	w4.name = "w4";
	name 	= "Car";

	attachChild(w1);
	attachChild(w2);
	attachChild(w3);
	attachChild(w4);

	attachChild(body);
	attachChild(front);
	attachChild(back);
	attachChild(window);
	attachChild(back);

	angle 	 = 0;
	location = loc;

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
//as well as the Car
//behaviors

void Car::moveUp() {
	//Add to y if moving up
	location.y   += .5;
	//Set angle and direction
	dir 		  = 'u';
	angle		  =  90;
}

void Car::moveDown() {
	//Subtract y if moving up
	location.y   -= .5;
	//Set angle and direction
	dir 		  = 'd';
	angle		  =  270;
}

void Car::moveLeft() {
	//Subtract x if moving left
	location.x     -= .5;
	//Set angle and direction
	dir 		    = 'l';
	angle		    =  180;
}

void Car::moveRight() {
	//Add x if moving right
	location.x   += .5;
	//Set angle and direction
	dir 		  = 'r';
	angle		  =   0;
}

void Car::moveUpRight() {
	//Move up and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .5/2;
	location.x   += .5/2;
	//Set angle and direction
	dir 		  = 'p';
	angle		  = 45;
}
void Car::moveUpLeft() {
	//Move up and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   += .5/2;
	location.x   -= .5/2;
	//Set angle and direction
	dir 		  = 'q';
	angle		  =  135;
}
void Car::moveDownRight() {
	//Move down and right
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .5/2;
	location.x   += .5/2;
	//Set angle and direction
	dir 		  = 'm';
	angle		  =  315;
}
void Car::moveDownLeft() {
	//Move down and left
	//Divide by 2 because
	//Both directions are
	//Being added to
	location.y   -= .5/2;
	location.x   -= .5/2;
	//Set angle and direction
	dir 		  =  'z';
	angle		  =  225;
}

struct CarFriend {
	Behavior* behavior;
	Node*	  model;
	CarFriend(Node& n, Behavior& b);
	int health;
};

CarFriend::CarFriend(Node& n, Behavior& b) {
	model 	 = &n;
	behavior = &b;
	health   = 2;
}

struct CarBehavior : public Behavior {

	bool isLeft;
	CarBehavior(bool left);
	void behave(Node &model);

};

CarBehavior::CarBehavior(bool left) {
	isLeft = left;
}

void CarBehavior::behave(Node &model) {  

	Car &car = (Car&) model;

	if (isLeft)
		car.moveLeft();
	else
		car.moveRight();
				
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/


#include <X11/Xlib.h>
#include <X11/keysym.h>

class InteractionManager {

	public:
		void update(Display *dpy);
		void check_mouse(XEvent *e);
		void check_keys(XEvent *e);
		bool leftClick, rightClick, esc, up, down, left, right, space;
		Vec  cursorLocation;

};

void InteractionManager::update(Display *dpy) {
	while (XPending(dpy)) {
		XEvent e;
		XNextEvent(dpy, &e);
		check_mouse(&e);
		check_keys(&e);
	}

}

void InteractionManager::check_mouse(XEvent *e) {

	static int savex = 0;
	static int savey = 0;
	static int n     = 0;

	if (e->type == ButtonRelease) {

		if (e->xbutton.button==1) {

			//Left button was pressed
			int y = WINDOW_HEIGHT - e->xbutton.y;
			int x = WINDOW_HEIGHT - e->xbutton.x;
			cursorLocation.x = x;
			cursorLocation.y = y;
			leftClick = false;
			return;

		}

		return;
	}

	if (e->type == ButtonPress) {

		if (e->xbutton.button==1) {

			//Left button was pressed
			int y = WINDOW_HEIGHT - e->xbutton.y;
			int x = WINDOW_HEIGHT - e->xbutton.x;
			cursorLocation.x = x;
			cursorLocation.y = y;
			leftClick = true;
			return;

		}

		if (e->xbutton.button==3) {
			//Right button was pressed
			return;
		}

	}

	//Did the mouse move?
	if (savex != e->xbutton.x || savey != e->xbutton.y) {

		savex = e->xbutton.x;
		savey = e->xbutton.y;

		cursorLocation.x = savex;
		cursorLocation.y = savey;

		if (++n < 10)
			return;

	}

}

void InteractionManager::check_keys(XEvent *e) {

	if (e->type == KeyRelease) {

		int key = XLookupKeysym(&e->xkey, 0);

		if (key == XK_Escape) {
			esc = false;
		}

		if (key == 65362) {
			up = false;
		}

		if (key == 65364) {
			down = false;
		}

		if (key == 65361) {
			left = false;
		}		

		if (key == 65363) {
			right = false;
		}	

		if (key == 32) {
			space = false;
		}

	}

	//Was there input from the keyboard?
	if (e->type == KeyPress) {

		int key = XLookupKeysym(&e->xkey, 0);

		if (key == XK_Escape) {
			esc = true;
		}

		if (key == 65362) {
			up = true;
		}

		if (key == 65364) {
			down = true;
		}

		if (key == 65361) {
			left = true;
		}		

		if (key == 65363) {
			right = true;
		}	

		if (key == 32) {
			space = true;
		}

	}

	return;

}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

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

//Constructor passes InteractionManager to PlayerManager
EntityManager:: EntityManager(InteractionManager &i) : pm(i) {
}

void EntityManager::updateBullets() {

	for (int i = 0; i < bulletCount; i++) {

		Bullet* cur = &bullets[i];
		float speed = 3;
		char   dir  = cur->dir;

		switch (dir) {
			
		case 'u':
			cur->body.location.y += speed;
			break;
		case 'd':
			cur->body.location.y -= speed;
			break;
		case 'l':
			cur->body.location.x -= speed;
			break;
		case 'r':
			cur->body.location.x += speed;
			break;
		case 'q':
			cur->body.location.x -= speed/2;
			cur->body.location.y += speed/2;
			break;
		case 'p':
			cur->body.location.x += speed/2;
			cur->body.location.y += speed/2;
			break;
		case 'z':
			cur->body.location.x -= speed/2;
			cur->body.location.y -= speed/2;
			break;
		case 'm':
			cur->body.location.x += speed/2;
			cur->body.location.y -= speed/2;
			break;

		}

		int x = cur->body.location.x;
		int y = cur->body.location.y;

		if (x > WINDOW_WIDTH || x < 0) {
			bullets[i] = bullets[bulletCount-1];
			bulletCount--;
		}

		else if (y > WINDOW_HEIGHT || y < 0 ) {
			bullets[i] = bullets[bulletCount-1];
			bulletCount--;
		}

	}
	
}

void EntityManager::checkCollision() {

	for (int i = 0; i < bulletCount; i++) {

		Shape* cur = &bullets[i].body;

		for (int j = 0; j < em.enemyCount; j++) {

			Node* ce = em.enemyNode.nodeArr[j];

			for (int k = 0; k < ce->shapeCount; k++) {

				Shape s = *ce->shapeArr[k];
				s.location.x += ce->location.x;
				s.location.y += ce->location.y;
				s.angle  	 += ce->angle;

				if (collides(s,*cur)) {
					Enemy *enemy = em.enemies[j];
					enemy->health--;
					bullets[i] = bullets[bulletCount-i];
					bulletCount--;
				}				
				
			}

		}

		for (int j = 0; j < fm.carCount; j++) {

			Node* cf = fm.carNode.nodeArr[j];

			for (int k = 0; k < cf->shapeCount; k++) {

				Shape s = *cf->shapeArr[k];
				s.location.x += cf->location.x;
				s.location.y += cf->location.y;

				if (collides(s,*cur)) {
					CarFriend *cf = fm.cars[j];
					cf->health--;
					bullets[i] = bullets[bulletCount-i];
					bulletCount--;
				}				
				
			}

		}
	
	}

}

bool EntityManager::collides(Shape s1, Shape s2) {

	int x1 = s1.location.x-5;
	int x2 = s2.location.x;

	int y1 = s1.location.y;
	int y2 = s2.location.y;

	if (x1 >= x2-s2.width && x1 <= x2+s2.width) {

		if (y1 >= y2-s2.height && y1 <= y2+s2.height) {
				return true;
		}

	}

	return false;

}

//Update Loop
void EntityManager::update() {
	updateBullets();
	checkCollision();
	pm.update();
	em.update();
	fm.update();
}


/*------------------------------------------------------------------------------------------------------------------------------------------*/

struct Game {

	Node			   rootNode;
	InteractionManager im;
	EntityManager	   entm;
	Hud hud;
	Game();
	void printDataTree();

};

//Game Constructor passes interactionmanager to entity manager
Game::Game() : entm(im), hud(rootNode) {
	//Name Root Node
	rootNode.name = "Root Node";
	//Attach Player and Enemy Nodes to Root Node
	rootNode.attachChild(entm.fm.streetNode);	
	rootNode.attachChild(entm.pm.playerNode);
	rootNode.attachChild(entm.em.enemyNode);
	rootNode.attachChild(entm.fm.carNode);
}

//Used to Print Games Data 
void Game::printDataTree() {

	std::cout << "\nGame Data:\n";

	std::cout << rootNode.name 	  << std::endl;
	std::cout << entm.pm.playerNode.name  << std::endl;
	std::cout << entm.pm.player.tank.name << std::endl;
	std::cout << entm.pm.player.tank.body.name << std::endl;
	std::cout << entm.pm.player.tank.gun.name << std::endl;
	std::cout << entm.pm.player.tank.hatch.name << std::endl;

	std::cout << "\n";

}

Game 		game; 			//Game struct defined in util/GameDef.h
/*------------------------------------------------------------------------------------------------------------------------------------------*/

#include <GL/glx.h>


//Cos by Degree
float cosByAngle(int angle) {

	float rad = angle*0.0174533;
	return cos(rad);

}

//Sin by Degree
float sinByAngle(int angle) {

	float rad = angle*0.0174533;
	return sin(rad);

}

float pointToDeg(float x, float y) {

	float rad = atan2(y, x);
	return rad * (180 / M_PI);

}

void angleTest() {

	float a = cosByAngle(90);
	float b = sinByAngle(90);

	std::cout << "Cos 90: " << a << " Sin 90: " << b << std:: endl;

	float w = pointToDeg(0,50);
	float x = pointToDeg(0,-25);
	float y = pointToDeg(-1,0);
	float z = pointToDeg(11,0);

	std::cout << " 0: " << w << " 180: " << x << " -90: " << y << " 90: " << z << std::endl;

}

class GlUtils {

	private:
		Window win;
		GLXContext glc;
		void set_title(void);
		void renderNode(Node *node);
		void drawBullets();
		void drawBox(Shape box);
		void drawBox(Shape *box);
	
	public:
		void    initXWindows(void);
		void    init_opengl(void);
		void    cleanupXWindows(void);
		void    render(Game *game);
		void 	render(Game &game);
		Display *dpy;

};

void GlUtils::set_title(void) {

	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Tank Blaster");

}

void GlUtils::cleanupXWindows(void) {

	cleanup_fonts();

	//do not change
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

}

void GlUtils::initXWindows(void) {


	//do not change
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	int w=WINDOW_WIDTH, h=WINDOW_HEIGHT;
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		std::cout << "\n\tcannot connect to X server\n" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		std::cout << "\n\tno appropriate visual found\n" << std::endl;
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		ButtonPress | ButtonReleaseMask | PointerMotionMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
		InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}

void GlUtils::init_opengl(void) {

	//OpenGL initialization
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//Set 2D mode (no perspective)
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
	//Set the screen background color
	//glClearColor(0.1, 0.1, 0.1, 1.0);
	glClearColor(.1, 1, .17, 1);
	//Allow Fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();

}

void GlUtils::drawBox(Shape box) {

	//std::cout << "Drawing Shape: " << box.name << " at: " << box.location.x << "," << box.location.y << "," << box.location.z << ",";
	//std::cout << " h: " << box.width << " w: " << box.height << " Angle: " << box.angle << std::endl;

	if (isnan(box.angle)) {box.angle = box.parent->angle;}

	glColor3ub(box.color.x,box.color.y,box.color.z);

	glPushMatrix();
	
	glTranslatef(box.location.x, box.location.y, 0);
	glRotatef(box.angle, 0, 0, 1);

	float w = box.width/2;
	float h = box.height/2;

	glBegin(GL_QUADS);
		glVertex2i(-w,-h);
		glVertex2i(-w, h);
		glVertex2i( w, h);
		glVertex2i( w,-h);
	glEnd();
	
	glPopMatrix();

}

void GlUtils::drawBox(Shape *box) {

	//printf("Drawing Shape: \n");
	//std::cout << box->location.x << " , " << box->location.y << std::endl;
	//std::cout << box->width << " , " << box->height << std::endl;
	//std::cout << "Drawing Shape: " << box->name << " at: " << box->location.x << "," << box->location.y << "," << box->location.z << ",";
	//std::cout << " h: " << box->width << " w: " << box->height << std::endl;

	glColor3ub(box->color.x,box->color.y,box->color.z);

	glPushMatrix();
	
	glTranslatef(box->location.x, box->location.y, box->location.z);
	glRotatef(box->angle, 0, 0, 1);

	float w = box->width/2;
	float h = box->height/2;

	glBegin(GL_QUADS);
		glVertex2i(-w,-h);
		glVertex2i(-w, h);
		glVertex2i( w, h);
		glVertex2i( w,-h);
	glEnd();
	
	glPopMatrix();

}



void GlUtils::drawBullets() {

	for (int i = 0; i < bulletCount; i++) {

		Bullet b = bullets[i];
		drawBox(b.body);

	}

}


//Recursively Renders a Node and All Children

void GlUtils::renderNode(Node *node) {

	//std::cout << "Attempting Render On Node: " << node->name << " Node Count: " << node->nodeCount << " Node Angle: "<< node->angle << " Shape Count: " << node->shapeCount << std::endl;
	
	//Render Shapes in Node
	for (int i =0; i < node->shapeCount; i++) {

		//Array is list of pointers
		Shape *ps = node->shapeArr[i];
		
		//Dereference as to not edit the actual location of the shape
		Shape s;
		s = *ps;
		s.name = ps->name;

		//std::cout << "Shape: " << s.name << " Angle Before: " << s.angle << " x before: " << s.location.x << " y before: " << s.location.y << std::endl;

		//Magnitude from center of parent
		float x	      = pow(s.location.x, 2);
		float y 	  = pow(s.location.y, 2);

		float mag    = x-y;

		//No Negative Square Roots
		if (mag<0) 
			mag *=-1;

		mag = sqrt(mag);

		//Apply Angle of Parent Node to Shape;
		s.angle      += node->angle;

		//Sets the location of the shape based on its
		//local translation multiplied by the cosine
		//and sine of the angle

		//Reference Angle is point from center of parent at angle 0
		float angle = pointToDeg(s.location.x, s.location.y);

		//Uses Magnitude times multiplied by sine and cosine of the angles will give the proper offset distance
		s.location.x  = mag * cosByAngle(s.angle+angle);	
		s.location.y  = mag * sinByAngle(s.angle+angle);

		//std::cout << "Shape: " << s.name << " x after: " << s.location.x << " y after: " << s.location.y << std::endl;
		//std::this_thread::sleep_for (std::chrono::seconds(1));

		//Sets the Location of the Node relative 
		//To its parent 
		s.location.x += node->location.x;	
		s.location.y += node->location.y;
		s.location.z += node->location.z;

		//Draw the translated and rotated shape
		drawBox(s);

	}

	//Render nodes recursively
	for (int i = 0; i < node->nodeCount; i++) {

		//Dereferenced copy of Node
		Node n = *node->nodeArr[i];

		//Apply Location and Angle of Parent
		//to local translation
		n.location.x += node->location.x;	
		n.location.y += node->location.y;
		n.location.z += node->location.z;
		n.angle      += node->angle;

		//Recursive Call
		renderNode(&n);

	}


}

void GlUtils::render(Game &game) {

	glClear(GL_COLOR_BUFFER_BIT);
	renderNode(&game.rootNode);
	drawBullets();
	game.hud.update();
	glXSwapBuffers(dpy, win);

}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

