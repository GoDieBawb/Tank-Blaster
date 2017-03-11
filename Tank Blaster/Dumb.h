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

#include "scene/ShapeDefs.h"
#include "entity/unit/Behavior.cpp"

struct Bullet {
	Shape body;
	char  dir;
};

#include "robertR.cpp"
#include "util/InteractionManager.cpp"
#include "util/GameDef.h"
#include "util/GlUtils.cpp"
