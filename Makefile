CC = g++
CFLAGS = -Wall -O2 -I "./include" -std=c++11

OBJS  = Box.o MathUtils.o Scene.o Sphere.o
OBJS += Camera.o Light.o ShaderProgram.o Vector4f.o
OBJS += Entity.o Mat4x4f.o Model.o SimpleModelEntity.o
OBJS += GContext.o Material.o Renderer.o   

all: libGiselle

libGiselle:	$(OBJS)
		ar -r libGiselle.a $^

.cpp.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f *.o libGiselle.a

