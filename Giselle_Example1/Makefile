CC = g++
CFLAGS = -std=c++11 `sdl-config --cflags` -I "../include"
LFLAGS = -L ".." `sdl-config --libs` -lGiselle -lGLEW -lGL

all:		Example1

Example1:	Example1.o
		$(CC) $^ -o $@ $(LFLAGS)

.cpp.o:		
		$(CC) $(CFLAGS) -c $^ -o $@

clean:
		rm -f *.o Example1

