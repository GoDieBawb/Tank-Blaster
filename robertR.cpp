//Name: Robert Ripley
//Description: Tank-Blaster Framework
//Course: CMPS3350
//Date: Spring 2017

/*----------------------------------------------------------------/
Global Declarations
*----------------------------------------------------------------*/

//Bullet stuff
Bullet bullets[1000];
int bulletCount = 0;

//Public Color Vector
Vec red    = Vec(255,0,0);
Vec green  = Vec(0,255,0);
Vec blue   = Vec(0,0,255);
Vec yellow = Vec(255,255,0);
Vec pink   = Vec(255,182,193);
Vec black  = Vec(0,0,0);

//Game struct holds and updates data managers
Game         game;

/*----------------------------------------------------------------/
Spatial Functions
Functionality: Abstract Spatial can be either Node or Spatial
*----------------------------------------------------------------*/

//Spatial constructor intializes angle to 0
Spatial::Spatial() {
    angle = 0;
}

/*----------------------------------------------------------------/
Shape functions
Functionality: Shape is a type of spatial that has an actual Geometry 
being drawn
*----------------------------------------------------------------*/

//Shape constructor gives shape generic name
Shape::Shape() {
    name = "S";
}

/*----------------------------------------------------------------/
Node Functions
Functionality: A Node is a Spatial that holds other Spatials
*----------------------------------------------------------------*/

//Construct Node
Node::Node() {
    name        = "N";
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

//Returns true if the node parameter is a child of the node
bool Node::hasChild(Node &n) {

    for (int i =0; i < nodeCount; i++) {

        if (nodeArr[i] == &n) {
            return true;
        }

    }

    return false;
}

//Returns true if shape parameter is a child of the node
bool Node::hasChild(Shape &s) {

    for (int i =0; i < shapeCount; i++) {

        if (shapeArr[i] == &s) {
            return true;
        }

    }

    return false;

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

/*----------------------------------------------------------------/
Car Functions
Functionality: Car is an extension of node. Is a model of a car and can move
*----------------------------------------------------------------*/

//Car Constructor. Creates a car and sets data members
Car::Car(Vec loc) {

    //Set piece shapes and colors
    Vec black(0,0,0);
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

    //Set piece locations
    body.location      = Vec(0,0,0);
    front.location     = Vec(10,0,0);
    back.location      = Vec(-10,0,0);
    w1.location        = Vec(9,6,0);
    w2.location        = Vec(9,-6,0);
    w3.location        = Vec(-9,6,0);
    w4.location        = Vec(-9,-6,0);
    window.location    = Vec(7,0,0);

    //Set piece names
    body.name   = "Body";
    front.name  = "Front";
    back.name   = "Back";
    window.name = "Window";
    w1.name     = "w1";
    w2.name     = "w2";
    w3.name     = "w3";
    w4.name     = "w4";
    name        = "Car";

    //Attach Pieces to nde
    attachChild(w1);
    attachChild(w2);
    attachChild(w3);
    attachChild(w4);

    attachChild(body);
    attachChild(front);
    attachChild(back);
    attachChild(window);
    attachChild(back);

    angle      = 0;
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
    dir           = 'u';
    angle          =  90;
}

void Car::moveDown() {
    //Subtract y if moving up
    location.y   -= .5;
    //Set angle and direction
    dir           = 'd';
    angle          =  270;
}

void Car::moveLeft() {
    //Subtract x if moving left
    location.x     -= .5;
    //Set angle and direction
    dir             = 'l';
    angle            =  180;
}

void Car::moveRight() {
    //Add x if moving right
    location.x   += .5;
    //Set angle and direction
    dir           = 'r';
    angle          =   0;
}

void Car::moveUpRight() {
    //Move up and right
    //Divide by 2 because
    //Both directions are
    //Being added to
    location.y   += .5/2;
    location.x   += .5/2;
    //Set angle and direction
    dir           = 'p';
    angle          = 45;
}
void Car::moveUpLeft() {
    //Move up and left
    //Divide by 2 because
    //Both directions are
    //Being added to
    location.y   += .5/2;
    location.x   -= .5/2;
    //Set angle and direction
    dir           = 'q';
    angle          =  135;
}
void Car::moveDownRight() {
    //Move down and right
    //Divide by 2 because
    //Both directions are
    //Being added to
    location.y   -= .5/2;
    location.x   += .5/2;
    //Set angle and direction
    dir           = 'm';
    angle          =  315;
}
void Car::moveDownLeft() {
    //Move down and left
    //Divide by 2 because
    //Both directions are
    //Being added to
    location.y   -= .5/2;
    location.x   -= .5/2;
    //Set angle and direction
    dir           =  'z';
    angle         =  225;
}

/*----------------------------------------------------------------/
Car Friend Functions
Functionality: Represents the friendly car. Holds a car model and a 
car friend behavior
*----------------------------------------------------------------*/

//Car Friend Constructor. Takes model and behavior. Sets health
CarFriend::CarFriend(Node& n, Behavior& b) {
    model    = &n;
    behavior = &b;
    health   = 2;
}

/*----------------------------------------------------------------/
Car Behavior Functions
Functionality: Car behavior makes car move left or right on behave
*----------------------------------------------------------------*/

//Construct car behavior. Car either drives left or right
CarBehavior::CarBehavior(bool left) {
    isLeft = left;
}

//Moves car left or right based on type
void CarBehavior::behave(Node &model) {  

    Car &car = (Car&) model;

    if (isLeft)
        car.moveLeft();
    else
        car.moveRight();
                
}


/*----------------------------------------------------------------/
Interaction Manager Functions
Functionality: Interaction Manager holds public booleans to show what 
keys are pressed as well as functions to act on key presses and mouse clicks.
*----------------------------------------------------------------*/

//Update loop for the interaction manager
void InteractionManager::update(Display *dpy) {
    while (XPending(dpy)) {
        XEvent e;
        XNextEvent(dpy, &e);
        check_mouse(&e);
        check_keys(&e);
    }

}

//Checks for the Mouse Pressed
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

//Check Keys for Press and Release
void InteractionManager::check_keys(XEvent *e) {

    if (e->type == KeyRelease) {

        int key = XLookupKeysym(&e->xkey, 0);

        if (key == XK_Escape) {
            esc = false;
        }

        if (key == 65293) {
            enter  = false;
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

        if (key == 65293) {
            enter = true;
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

/*----------------------------------------------------------------/
Entity Manager Functions
Functionality: Entity Manager is responsible for holding the data 
managers for the player friendlies and enemies. This class also 
checks for collisions and updates the bullets. It updates the data 
managers via its update loop.
*----------------------------------------------------------------*/


//Constructor passes InteractionManager to PlayerManager
EntityManager:: EntityManager(InteractionManager &i) : pm(i) {
}

//Moves each bullet and checks position for removal
void EntityManager::updateBullets() {

    //For each bullet
    for (int i = 0; i < bulletCount; i++) {

        Bullet* cur = &bullets[i];
        float speed = 3;
        char   dir  = cur->dir;

        //Move bullets based on direction
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

        //Check for off screen
        int x = cur->body.location.x;
        int y = cur->body.location.y;

        if (x > WINDOW_WIDTH || x < 0) {
            bullets[i] = bullets[bulletCount-1];
            bulletCount--;
        }

        else if (y >= WINDOW_HEIGHT - WINDOW_HEIGHT/10 || y < 0 ) {
            bullets[i] = bullets[bulletCount-1];
            bulletCount--;
        }

    }
    
}

//Check for collisions between bullets
//Entities and the Player
void EntityManager::checkCollision() {

    Player *player = &pm.player;

    //Bullet Collision
    for (int i = 0; i < bulletCount; i++) {

        Shape cur = bullets[i].body;
        cur.location.x += 10;

        //Check Bullet hitting enemy
        for (int j = 0; j < em.enemyCount; j++) {

            Node* ce = em.enemyNode.nodeArr[j];

            for (int k = 0; k < ce->shapeCount; k++) {

                Shape s = *ce->shapeArr[k];
                s.location.x += ce->location.x;
                s.location.y += ce->location.y;
                s.angle       += ce->angle;

                if (collides(s,cur)) {
                    Enemy *enemy = em.enemies[j];
                    enemy->health--;
                    bullets[i] = bullets[bulletCount-i];
                    bulletCount--;
                    break;
                }                
                
            }

        }

        //Check for bullet hitting a friendly
        for (int j = 0; j < fm.carCount; j++) {

            Node* cf = fm.carNode.nodeArr[j];

            for (int k = 0; k < cf->shapeCount; k++) {

                Shape s = *cf->shapeArr[k];
                s.location.x += cf->location.x;
                s.location.y += cf->location.y;

                if (collides(s,cur)) {
                    CarFriend *cf = fm.cars[j];
                    cf->health--;
                    bullets[i] = bullets[bulletCount-i];
                    bulletCount--;
                    break;
                }                
                
            }

        }


        //Check for the bullet hitting a tank
        for (int k = 0; k < player->tank.shapeCount; k++) {

            Shape s       = *player->tank.shapeArr[k];
            s.location.x += player->tank.location.x;
            s.location.y += player->tank.location.y;
            s.angle       += player->tank.angle;

            if (collides(s, cur)) {
                player->health--;
                bullets[i] = bullets[bulletCount-i];
                bulletCount--;
                if (player->health < 0) player->health=0;
                break;
            }        
    
        }
    
    }

    //Player Collision With Entities
    for (int k = 0; k < player->tank.shapeCount; k++) {

        Shape s       = *player->tank.shapeArr[k];
        s.location.x += player->tank.location.x;
        s.location.y += player->tank.location.y;
        s.angle       += player->tank.angle;

        //Enemy Check
        for (int j = 0; j < em.enemyCount; j++) {

            Node* ce = em.enemyNode.nodeArr[j];

            for (int i = 0; i < ce->shapeCount; i++) {

                Shape cur       = *ce->shapeArr[i];
                cur.location.x += ce->location.x;
                cur.location.y += ce->location.y;
                cur.angle         += ce->angle;

                if (collides(s,cur)) {
                    Enemy *enemy = em.enemies[j];
                    enemy->health=0;
                    player->health=0;
                    break;
                }                
                
            }

        }

        //Car Check
        for (int h = 0; h < fm.carNode.nodeCount; h++) {

            Node* cf = fm.carNode.nodeArr[h];

            for (int i = 0; i < cf->shapeCount; i++) {

                Shape cur       = *cf->shapeArr[i];
                cur.location.x += cf->location.x;
                cur.location.y += cf->location.y;
                cur.angle         += cf->angle;

                if (collides(s,cur)) {
                    CarFriend *car = fm.cars[h];
                    car->health    = 0;
                    player->health = 0;
                    break;
                }                
                
            }

        }

        //Tower Check
        for (int i = 0; i < 2; i++) {

            Node t;
            if (i==0) t = fm.leftTower;
            else       t = fm.rightTower;

            for (int j = 0; j < t.shapeCount; j++) {

                Shape cur         = *t.shapeArr[j];
                cur.location.x += t.location.x;
                cur.location.y += t.location.y;
                cur.angle         += t.angle;

                if (collides(s,cur)) {
                    player->health=0;
                    break;
                }    

            }
    
        }
    
    }

}

//Returns true if two shapes collide
bool EntityManager::collides(Shape s1, Shape s2) {

    float x1 = s1.location.x;
    float y1 = s1.location.y;

    float w1 = s1.width;
    float h1 = s1.height;

    float x2 = s2.location.x;
    float y2 = s2.location.y;

    float w2 = s2.width;
    float h2 = s2.height;




    if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && h1 + y1 > y2) {
        return true;
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

/*----------------------------------------------------------------/
Game Functions
Functionality: Game structure is the root of the game. Holds the entity 
manager, the hud, interaction manager and the root node.
*----------------------------------------------------------------*/

//Game Constructor passes interactionmanager to entity manager
Game::Game() : entm(im) {
    //Name Root Node
    rootNode.name = "Root Node";
    //Attach Player and Enemy Nodes to Root Node
    rootNode.attachChild(entm.fm.streetNode);    
    rootNode.attachChild(entm.pm.playerNode);
    rootNode.attachChild(entm.em.enemyNode);
    rootNode.attachChild(entm.fm.carNode);
    rootNode.attachChild(hud.hudNode);
}

//Used to Print Games Data 
void Game::printDataTree() {

    std::cout << "\nGame Data:\n";

    std::cout << rootNode.name       << std::endl;
    std::cout << entm.pm.playerNode.name  << std::endl;
    std::cout << entm.pm.player.tank.name << std::endl;
    std::cout << entm.pm.player.tank.body.name << std::endl;
    std::cout << entm.pm.player.tank.gun.name << std::endl;
    std::cout << entm.pm.player.tank.hatch.name << std::endl;

    std::cout << "\n";

}

/*----------------------------------------------------------------/
GL Utility Functions
Functionality: GlUtils hold the render logic of the game. It initializes the 
GL members and contains the logic necessary to act on spatials rotation, 
locations, angles, and sizes.
*----------------------------------------------------------------*/


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

//arch tangent to degrees
float pointToDeg(float x, float y) {

    float rad = atan2(y, x);
    return rad * (180 / M_PI);

}

//Debug Test for a reference angle. 
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

//Initialize Display
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

//Init Open GL
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


//Draw Box
void GlUtils::drawBox(Shape box) {

    //Ensure no isnan error from offset stuff
    if (isnan(box.angle)) {box.angle = box.parent->angle;}
    
    //Set color of box
    glColor3ub(box.color.x,box.color.y,box.color.z);

    glPushMatrix();
    
    //Set location
    glTranslatef(box.location.x, box.location.y, 0);
    //Set angle    
    glRotatef(box.angle, 0, 0, 1);

    //Set width and height /2
    float w = box.width/2;
    float h = box.height/2;

    //Actually draw the box
    glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w, h);
        glVertex2i( w, h);
        glVertex2i( w,-h);
    glEnd();
    
    glPopMatrix();

}

//Draw the Bullets
void GlUtils::drawBullets() {

    for (int i = 0; i < bulletCount; i++) {

        Bullet b = bullets[i];
        drawBox(b.body);

    }

}


//Recursively Renders a Node and All Children
void GlUtils::renderNode(Node *node) {

    //Render Shapes in Node
    for (int i =0; i < node->shapeCount; i++) {

        //Array is list of pointers
        Shape *ps = node->shapeArr[i];
        
        //Dereference as to not edit the actual location of the shape
        Shape s;
        s = *ps;
        s.name = ps->name;

        //Magnitude from center of parent
        float x          = pow(s.location.x, 2);
        float y       = pow(s.location.y, 2);

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

        //Uses Magnitude times multiplied by sine and cosine of the angles will give the proper 
        //offset distance
        s.location.x  = mag * cosByAngle(s.angle+angle);    
        s.location.y  = mag * sinByAngle(s.angle+angle);

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

//Render Game
void GlUtils::render(Game &game) {

    glClear(GL_COLOR_BUFFER_BIT);
    renderNode(&game.rootNode);
    drawBullets();
    game.hud.update();
    glXSwapBuffers(dpy, win);

}

/*----------------------------------------------------------------*/

