CC = g++

CFLAGS = -Wall -std=c++11 -ggdb -O3 -fopenmp

INCLUDES = -Iglm

OBJS = ImageWriter.o Camera.o Scene.o Sphere.o Material.o Object.o PathTraceCamera.o DiffGeomData.o IlluminationSolver.o

all: src/main.cpp $(OBJS)
	$(CC) $(CFLAGS) src/main.cpp $(OBJS) -o bin/main $(INCLUDES)

ImageWriter.o: src/ImageWriter.cpp
	$(CC) $(CFLAGS) -c src/ImageWriter.cpp $(INCLUDES)

Camera.o: src/Camera.cpp
	$(CC) $(CFLAGS) -c src/Camera.cpp $(INCLUDES)

PathTraceCamera.o: src/PathTraceCamera.cpp
	$(CC) $(CFLAGS) -c src/PathTraceCamera.cpp $(INCLUDES)

Scene.o: src/Scene.cpp
	$(CC) $(CFLAGS) -c src/Scene.cpp $(INCLUDES)

Sphere.o: src/Sphere.cpp
	$(CC) $(CFLAGS) -c src/Sphere.cpp $(INCLUDES)

Material.o: src/Material.cpp
	$(CC) $(CFLAGS) -c src/Material.cpp $(INCLUDES)

Object.o: src/Object.cpp
	$(CC) $(CFLAGS) -c src/Object.cpp $(INCLUDES)

DiffGeomData.o: src/DiffGeomData.cpp
	$(CC) $(CFLAGS) -c src/DiffGeomData.cpp $(INCLUDES)

IlluminationSolver.o: src/IlluminationSolver.cpp
	$(CC) $(CFLAGS) -c src/IlluminationSolver.cpp $(INCLUDES)

clean:
	rm *.o
