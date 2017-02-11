#include <X11/Xlib.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
