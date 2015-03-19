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
#include "Sphere.hpp"

int main( int argc, char** argv )
{
	if( argc < 2){
		std::cout << "Insert a name for the generated image (with .ppm extension)" << std::endl;
		return -1;
	}

	std::string filename = argv[1];

	std::cout << "RayTracer v0.1" << std::endl;
	std::cout << "Rendering scene..." << std::endl;

	Camera camera( 640, 480 );
	camera.planeSize = glm::vec2( 6.4f, 4.8f );
	camera.focalDistance = 3.0f;
	camera.position += glm::vec3( 0,0, 5 );
	
	std::shared_ptr<Scene> scene( new Scene() );

	std::shared_ptr<Sphere> light( new Sphere() );
	light->center = glm::vec3( 3, 30, -18 );
	light->radius = 1.0f;
	light->material.diffuseColor = RGB(1,1,1);
	light->material.luminosity = RGB(1,1,1);

	std::shared_ptr<Sphere> light2( new Sphere() );
	light2->center = glm::vec3( 3, 10, 20 );
	light2->radius = 1.0f;
	light2->material.diffuseColor = RGB(1,1,1);
	light2->material.luminosity = RGB(0.3);

	std::shared_ptr<Sphere> sphere1( new Sphere() );
	sphere1->center = glm::vec3( 0, 0, -20 );
	sphere1->radius = 9.0f;
	sphere1->material.diffuseColor = RGB(1,0.2,0.1);
	sphere1->material.specularColor = RGB(1,0.6,0.6);
	sphere1->material.reflectiveness = 0.01;

	std::shared_ptr<Sphere> sphere2( new Sphere() );
	sphere2->center = glm::vec3( 4, 4, -8 );
	sphere2->radius = 3.0f;
	sphere2->material.diffuseColor = RGB(0.1,1,0.02);
	sphere2->material.shininess = 50.0f;
	sphere2->material.reflectiveness = 0.8f;

	std::shared_ptr<Sphere> almostPlane( new Sphere() );
	almostPlane->center = glm::vec3( 0, -100020, 0 );
	almostPlane->radius = 100000.0f;
	almostPlane->material.diffuseColor = RGB(1,1,1);

	scene->addObject( std::dynamic_pointer_cast<Object>(sphere1) );
	scene->addObject( std::dynamic_pointer_cast<Object>(sphere2) );
	scene->addObject( std::dynamic_pointer_cast<Object>(light) );
	scene->addObject( std::dynamic_pointer_cast<Object>(light2) );
	scene->addObject( std::dynamic_pointer_cast<Object>(almostPlane) );

	camera.render( *scene );

	ImageWriter imWriter( camera.image );
	imWriter.writeOnPPM( filename );
	
	std::cout << "Done. Viewing image..." << std::endl;
	system( ("eog " + filename).c_str());

	return 0;
}
