#include <GL/glx.h>


extern "C" {
	#include "fonts.h"
}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


float cosByAngle(int angle) {

	float rad = angle*0.0174533;
	return cos(rad);

}

float sinByAngle(int angle) {

	float rad = angle*0.0174533;
	return sin(rad);

}

class GlUtils {

	private:
		Window win;
		GLXContext glc;
		void renderNode(Node *node);
		//void drawBullets(Game *game);
		void drawBox(Shape box);
		void drawBox(Shape *box);
	
	public:
		void    initXWindows(void);
		void    init_opengl(void);
		void    cleanupXWindows(void);
		void    render(Game *game);
		void    set_title(void);
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

	//printf("Drawing Shape: \n");
	//std::cout << box.location.x << " , " << box.location.y << std::endl;
	//std::cout << box.width << " , " << box.height << std::endl;
	//std::cout << "Drawing Shape: " << box.name << " at: " << box.location.x << "," << box.location.y << "," << box.location.z << ",";
	//std::cout << " h: " << box.width << " w: " << box.height << std::endl;

	glColor3ub(box.color.x,box.color.y,box.color.z);

	glPushMatrix();
	
	glTranslatef(box.location.x, box.location.y, box.location.z);
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


/*
void GlUtils::drawBullets(Game *game) {

	for (int i = 0; i < game->bulletCount; i++) {

		Bullet *b = &game->bullets[i];
		drawBox(b->body);

	}

}
*/

void GlUtils::renderNode(Node *node) {

	//std::string a;
	//int childCount = node->nodeCount + node->shapeCount;
	//std::cout << "Attempting Render On Node: " << node->name << " Node Count: " << node->nodeCount << " Shape Count: " << node->shapeCount << std::endl;
	//std::cout << "\n";
	
	//Render Shapes in Node
	for (int i =0; i < node->shapeCount; i++) {

		//Array is list of pointers
		Shape *ps = node->shapeArr[i];
		
		//Dereference as to not edit the actual location of the shape
		Shape s;
		s = *ps;

		//Dist from center of parent
		float x	      = pow(0 - s.location.x, 2);
		float y 	  = pow(0 - s.location.y, 2);

		float dist    = x-y;
		
		//No Negative Square Roots
		if (dist<0)
			dist*=-1;

		dist		  = sqrt(dist);

		//Apply Angle of Parent Node to Shape;
		s.angle      += node->angle;

		//Work to be done here
		
		/* This assumed that the child shape is */
		/* Offset By either X **OR** Y			*/
		/* Needs Vector Normalization			*/

		//Sets the location of the shape based on its
		//local translation multiplied by the cosine
		// and sine of the angle
		//Needs normalized vectors for more flexibility
		s.location.x  = dist * cosByAngle(s.angle);	
		s.location.y  = dist * sinByAngle(s.angle);


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

	//drawTank(*game->player);
	//drawBullets(game);
	renderNode(&game.rootNode);

	glXSwapBuffers(dpy, win);

}

