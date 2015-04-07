#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>

#include "glm.hpp"
#include "aliases.hpp"
#include "Image.hpp"
#include "ImageWriter.hpp"
#include "Camera.hpp"
#include "PathTraceCamera.hpp"
#include "Sphere.hpp"

int main( int argc, char** argv )
{
    if( argc < 2){
        std::cout << "Insert a name for the generated image (with .ppm extension)" << std::endl;
        return -1;
    }

    std::string filename = argv[1];

//    Uncomment the following line to test
//    std::string filename = "path_test.ppm";

	std::cout << "RayTracer v0.1" << std::endl;
	std::cout << "Rendering scene..." << std::endl;

    PathTraceCamera camera( 640, 480, 10 );
    camera.planeSize = 2.0f*glm::vec2( 6.4f, 4.8f );
    camera.focalDistance = 6.0f;
    camera.position += glm::vec3( 0,0, 35 );
	
	std::shared_ptr<Scene> scene( new Scene() );

	std::shared_ptr<Sphere> light( new Sphere() );
    light->center = glm::vec3( 0, 38, -20);
    light->radius = 6.0f;
	light->material.diffuseColor = RGB(1,1,1);
    light->material.luminosity = RGB(1,1,1);
    light->material.power = 50.0f;

	std::shared_ptr<Sphere> sphere1( new Sphere() );
    sphere1->center = glm::vec3( 6, -27, -20 );
    sphere1->radius = 13.0f;
	sphere1->material.diffuseColor = RGB(1,1,1);

	std::shared_ptr<Sphere> sphere2( new Sphere() );
    sphere2->center = glm::vec3( -28, -30, -30 );
    sphere2->radius = 8.0f;
    sphere2->material.diffuseColor = RGB(0,0.4,1);

	std::shared_ptr<Sphere> backWall( new Sphere() );
	backWall->center = glm::vec3( 0, 0, -100050 );
	backWall->radius = 100000.0f;
	backWall->material.diffuseColor = RGB(1,1,1);

    std::shared_ptr<Sphere> frontWall( new Sphere() );
    frontWall->center = glm::vec3( 0, 0, 100100 );
    frontWall->radius = 100000.0f;
    frontWall->material.diffuseColor = RGB(1,1,1);

	std::shared_ptr<Sphere> leftWall( new Sphere() );
	leftWall->center = glm::vec3( -100040, 0, 0);
	leftWall->radius = 100000.0f;
	leftWall->material.diffuseColor = RGB(1,0,0);

	std::shared_ptr<Sphere> rightWall( new Sphere() );
	rightWall->center = glm::vec3( 100040, 0, 0);
	rightWall->radius = 100000.0f;
	rightWall->material.diffuseColor = RGB(0,1,0);

	std::shared_ptr<Sphere> roof( new Sphere() );
	roof->center = glm::vec3( 0, 100040, 0);
	roof->radius = 100000.0f;
	roof->material.diffuseColor = RGB(1,1,1);

	std::shared_ptr<Sphere> almostPlane( new Sphere() );
	almostPlane->center = glm::vec3( 0, -100040, 0 );
	almostPlane->radius = 100000.0f;
	almostPlane->material.diffuseColor = RGB(1,1,1);

	scene->addObject( std::dynamic_pointer_cast<Object>(sphere1) );
	scene->addObject( std::dynamic_pointer_cast<Object>(sphere2) );
	scene->addObject( std::dynamic_pointer_cast<Object>(backWall) );
	scene->addObject( std::dynamic_pointer_cast<Object>(leftWall) );
	scene->addObject( std::dynamic_pointer_cast<Object>(rightWall) );
    scene->addObject( std::dynamic_pointer_cast<Object>(frontWall) );
	scene->addObject( std::dynamic_pointer_cast<Object>(roof) );
	scene->addObject( std::dynamic_pointer_cast<Object>(light) );
	scene->addObject( std::dynamic_pointer_cast<Object>(almostPlane) );

	camera.render( *scene );

	ImageWriter imWriter( camera.image );
	imWriter.writeOnPPM( filename );
	
	std::cout << "Done. Viewing image..." << std::endl;
	system( ("eog " + filename).c_str());

	return 0;
}
