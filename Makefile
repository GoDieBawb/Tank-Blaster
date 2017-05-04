all: TankBlaster

TankBlaster: TankBlaster.cpp
	g++ TankBlaster.cpp ./util/libggfonts.a -Wall -o TankBlaster -lX11 -lGL -lGLU -lm -g -include util.h -include robertR.h -include robertR.cpp -include obosaO.cpp -include jamesK.cpp -include bijanM.cpp -D noaudio #-lalut /usr/local/lib/libopenal.so.1 #-lalut /usr/lib/x86_64-linux-gnu/libopenal.so.1


clean:
	rm -f TankBlaster
	rm -f *.o
