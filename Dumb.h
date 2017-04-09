static float tpf;
static float osDiv;

//probably won't stay here
//#define WINDOW_WIDTH  800
//#define WINDOW_HEIGHT 600

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <math.h>
#include <cmath>
#include <stdio.h>
extern "C" {
#include "util/fonts.h"
}

#include "scene/ShapeDefs.h"
#include "entity/unit/Behavior.cpp"

Vec red    = Vec(255,0,0);
Vec green  = Vec(0,255,0);
Vec blue   = Vec(0,0,255);
Vec yellow = Vec(255,255,0);
Vec pink   = Vec(255,182,193);
Vec black  = Vec(0,0,0);

struct Bullet {
	Shape body;
	char  dir;
	char  source;
};
Bullet bullets[500];
int bulletCount = 0;

#include "robertR.cpp"
#include "util/InteractionManager.cpp"
#include "util/GameDef.h"
#include "gui/Hud.cpp"
#include "util/GlUtils.cpp"
