//Name: Robert Ripley
//Description: Tank-Blaster Framework
//Course: CMPS3350
//Date: Spring 2017

//Functionality: Basic 3f Vector
struct Vec {
    float x, y, z;       //Three float vector
    Vec() {x=0;y=0;z=0;} //Constructor initializes values to 0
    Vec(float x, float y, float z) { //Setter Constructor
	this->x = x; this->y = y; this->z=z;
    };
};


class Node; //Forward declaration

//Functionality: Abstract Spatial can be either Node or Spatial
class Spatial {

    public:
        Spatial();        //Declare Constructor
        Vec location;     //Location of Spatial
        float angle;      //Angle of Spatial
        std::string name; //Name of Spatial
        Node *parent;     //Has a parent Node
        Node getParent(); //Returns the parent Node

};

//Functionality: Shape is a type of spatial that has an actual Geometry 
//being drawn
class Shape: public Spatial {

    public:
        float width, height; //Width and height of shape if box
        float radius;        //Radius of shape if circle
        Vec color;           //Color of shape
        Shape();             //Declare Constructor

};


//Functionality: A Node is a Spatial that holds other Spatials
class Node: public Spatial {

    public:
        Node();
        Node  *nodeArr[15];         //Array Of Child Nodes
        Shape *shapeArr[15];        //Array of Child Shapes
        int  shapeCount;            //Size of Shape Array
        int  nodeCount;             //Size of Node Array
        void attachChild(Shape &s); //Attach a shape to Node
        void attachChild(Node  &n); //Attach a node to Node
        void detachChild(Node &n);  //Remove node from node
        void detachChild(Shape &s); //Remove shape from node
        bool hasChild(Node &n);     //Returns true if node has parameter child
        bool hasChild(Shape &s);    //Returns true if node has parameter child
        void printTree();           //Prints Nodes children

};

//Functionality: Abstract Structure with a single function
struct Behavior {
    virtual void behave(Node &model) = 0; //function will be called by derived
    virtual ~Behavior(){}; //Virtual constructor for abstract class
};


//Functionality: Bullet Structure
struct Bullet {
    Shape body;    //Actual shape of the bullet
    char  dir;     //Direction of travel
    char  source;  //Source of bullet player enemy or tower
};

//Functionality: Car is an extension of node. Is a model of a car and can move
class Car: public Node {

    private:
        char dir; //Direction of travel

    public:
        Shape body,front,back,window,w1,w2,w3,w4; //Shapes of car pieces
        Car(Vec loc);             //Constructor takes starting spot
        void   moveRight();       //moves car right
        void   moveLeft();        //moves car left
        void   moveUp();          //moves car up
        void   moveDown();        //moves car down
        void   moveUpLeft();      //moves car left and up
        void   moveUpRight();     //moves car right and up
        void   moveDownLeft();    //moves car left and down
        void   moveDownRight();   //moves car right and down

};

//Functionality: Represents the friendly car. Holds a car model and 
//a car friend behavior
struct CarFriend {
    Behavior* behavior; //Car friend abstract behavior
    Node*      model;   //Model of car
    CarFriend(Node& n, Behavior& b); //Constructor takes model and behavior
    int health; //Health of car
};

//Functionality: Car behavior makes car move left or right on behave
struct CarBehavior : public Behavior {
    bool isLeft;              //Determines whether car is left or right
    CarBehavior(bool left);   //Car Behavior Constructor
    void behave(Node &model); //Implements behave function
};

//Functionality: Interaction Manager holds public booleans to show 
//what keys are pressed as well as functions to act on key presses and 
//mouse clicks
class InteractionManager {

    public:
        void update(Display *dpy);   //Update loop takes display
        void check_mouse(XEvent *e); //Checks for mouse actions
        void check_keys(XEvent *e);  //Checks for key presses
		//bools for presses
        bool leftClick, rightClick, esc, up, down, left, right, space, enter;
        Vec  cursorLocation; //Location of thge cursor

};

//These have to be included here
//These depend on prior declarations
//While future declarations depend on these
#include "bijanM.h"
#include "obosaO.h"
#include "jamesK.h"

//Functionality: Entity Manager is responsible for holding the data 
//managers for the player friendlies and enemies. This class also 
//checks for collisions and updates the bullets.
//It also updates the data managers via its update loop.
class EntityManager {

    public:
        PlayerManager   pm; //Player Manager
        EnemyManager    em; //Enemy Manager
        FriendlyManager fm; //Friendly Manager
        EntityManager(InteractionManager &i); //Entity Manager constructor
        void update(); //update loop
        void updateBullets(); //updates bullets locations and removal
        void checkCollision(); //Checks for collisions between entities
        bool collides(Shape s1, Shape s2); //Returns true if shapes collide

};

//Functionality: Game structure is the root of the game. Holds the entity 
//manager, the hud, interaction manager and the root node.
struct Game {

    Node               rootNode; //Base node. All nodes are rendered from here
    InteractionManager im;       //Interaction Manager checks keys
    EntityManager      entm;     //Entity Manager manages entities
    Hud hud;                     //Heads up display for gui
    Game();                      //Constructor declaration
    void printDataTree();        //prints some debug info about the game

};

//Functionality: GlUtils hold the render logic of the game. It initializes 
//the GL Members And contains the logic necessary to act on spatials rotation, 
//locations, angles, and sizes.
class GlUtils {

    private:
        Window win;                  W//GL Window
        GLXContext glc;              //GL Context
        void set_title(void);        //Sets window title
        void renderNode(Node *node); //Renders Node recursively
        void drawBullets();          //Draws bullets to the screen
        void drawBox(Shape box);     //Draws a box shape
    
    public:
        void    initXWindows(void);    //initialize window
        void    init_opengl(void);     //initialize open gl
        void    cleanupXWindows(void); //cleans up window
        void    render(Game *game);    //renders hud and root node
        void     render(Game &game);   //renders hud and root nde
        Display *dpy;                  //Game Display

};

