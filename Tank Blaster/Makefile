# cs335 lab1
# to compile your project, type make and press enter

all: TankBlaster

TankBlaster: TankBlaster.cpp
	g++ TankBlaster.cpp ./util/libggfonts.a -Wall -oTankBlaster -lX11 -lGL -lGLU -lm -g -std=c++11 -include Dumb.h -include entity/unit/Car/robertR.cpp -include entity/unit/Tower/bijanM.cpp -include obosaO.cpp -include entity/unit/Tank/jamesK.cpp


clean:
	rm -f TankBlaster
	rm -f *.o

