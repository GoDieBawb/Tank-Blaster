# cs335 lab1
# to compile your project, type make and press enter

all: TankBlaster

TankBlaster: TankBlaster.cpp
	g++ TankBlaster.cpp ./util/libggfonts.a -Wall -o TankBlaster -lX11 -lGL -lGLU -lm -g -include Dumb.h -include robertR.cpp -include jamesK.cpp -include bijanM.cpp -include obosaO.cpp -D noaudio #-lalut /usr/local/lib/libopenal.so.1



clean:
	rm -f TankBlaster
	rm -f *.o

