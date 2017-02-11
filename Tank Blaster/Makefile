# cs335 lab1
# to compile your project, type make and press enter

all: TankBlaster

TankBlaster: TankBlaster.cpp
	g++ TankBlaster.cpp ./util/libggfonts.a -Wall -oTankBlaster -lX11 -lGL -lGLU -lm -g

clean:
	rm -f TankBlaster
	rm -f *.o

