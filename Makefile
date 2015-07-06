CC = g++

CFLAGS = -Wall -std=c++11 -ggdb -O3 -fopenmp

INCLUDES = -Iglm

OBJS = ImageWriter.o Camera.o Scene.o Sphere.o Material.o Object.o MultiSampledCamera.o DiffGeomData.o IlluminationSolver.o DirectIlluminationSolver.o SimpleCamera.o BxDF.o MirrorBRDF.o LambertianBRDF.o PTIlluminationSolver.o PerfectRefractionBTDF.o Fresnel.o FresnelDieletric.o FresnelConductor.o

all: src/main.cpp src/tst/tstBxDF.cpp $(OBJS)
	$(CC) $(CFLAGS) src/main.cpp $(OBJS) -o bin/main $(INCLUDES)
	$(CC) $(CFLAGS) src/tst/tstBxDF.cpp $(OBJS) -o bin/tstBxDF $(INCLUDES)

ImageWriter.o: src/ImageWriter.cpp
	$(CC) $(CFLAGS) -c src/ImageWriter.cpp $(INCLUDES)

Camera.o: src/Camera.cpp
	$(CC) $(CFLAGS) -c src/Camera.cpp $(INCLUDES)

MultiSampledCamera.o: src/MultiSampledCamera.cpp
	$(CC) $(CFLAGS) -c src/MultiSampledCamera.cpp $(INCLUDES)

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

DirectIlluminationSolver.o: src/DirectIlluminationSolver.cpp
	$(CC) $(CFLAGS) -c src/DirectIlluminationSolver.cpp $(INCLUDES)

SimpleCamera.o: src/SimpleCamera.cpp
	$(CC) $(CFLAGS) -c src/SimpleCamera.cpp $(INCLUDES)

BxDF.o: src/BxDF.cpp
	$(CC) $(CFLAGS) -c src/BxDF.cpp $(INCLUDES)

MirrorBRDF.o: src/MirrorBRDF.cpp
	$(CC) $(CFLAGS) -c src/MirrorBRDF.cpp $(INCLUDES)

LambertianBRDF.o: src/LambertianBRDF.cpp
	$(CC) $(CFLAGS) -c src/LambertianBRDF.cpp $(INCLUDES)

PTIlluminationSolver.o: src/PTIlluminationSolver.cpp
	$(CC) $(CFLAGS) -c src/PTIlluminationSolver.cpp $(INCLUDES)

PerfectRefractionBTDF.o: src/PerfectRefractionBTDF.cpp
	$(CC) $(CFLAGS) -c src/PerfectRefractionBTDF.cpp $(INCLUDES)

Fresnel.o: src/Fresnel.cpp
	$(CC) $(CFLAGS) -c src/Fresnel.cpp $(INCLUDES)

FresnelDieletric.o: src/FresnelDieletric.cpp
	$(CC) $(CFLAGS) -c src/FresnelDieletric.cpp $(INCLUDES)

FresnelConductor.o: src/FresnelConductor.cpp
	$(CC) $(CFLAGS) -c src/FresnelConductor.cpp $(INCLUDES)

clean:
	rm *.o
