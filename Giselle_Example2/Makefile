CC = g++
CFLAGS = -Wall -std=c++11 -g -I "../include"
LFLAGS = -L ".." -lGiselle -lglut -lGLEW -lGL

all:		Example2

Example2:	Example2.o
		$(CC) $^ -o $@ $(LFLAGS)

.cpp.o:		
		$(CC) $(CFLAGS) -c $^ -o $@

clean:
		rm -f *.o Example2

