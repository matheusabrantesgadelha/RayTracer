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
#include "MultiSampledCamera.hpp"
#include "DirectIlluminationSolver.hpp"
#include "Sphere.hpp"
#include "SimpleCamera.hpp"
#include "LambertianBRDF.hpp"
#include "MirrorBRDF.hpp"
#include "PTIlluminationSolver.hpp"
#include "BPTIlluminationSolver.hpp"
#include "PerfectRefractionBTDF.hpp"

//#define RELEASE

glm::vec3 mirrorSample( const glm::vec3 _normal, const glm::vec3 _light )
{
    glm::vec3 reflectedLight = glm::reflect( _light, _normal );
    return reflectedLight;
}

RGB mirrorBRDF(const glm::vec3 _in, const glm::vec3 _out, const glm::vec3 _normal, Material _m)
{
    glm::vec3 refLight = glm::reflect(_in, _normal);
    if( std::abs(glm::dot(_out,refLight)) >= 0.9999f ) return _m.albedo;// * POW_PI_MINUS_1;
    else return RGB(0,0,0);
}

int main( int argc, char** argv )
{
#ifdef RELEASE

    if( argc < 2) {
        std::cout << "Insert a name for the generated image (with .ppm extension)" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
#else
    std::string filename = "path_test.ppm";
#endif

	RGB silverEta( 0.177f );
	RGB silverK( 3.638f );
	std::shared_ptr<FresnelConductor> silverFresnel( new FresnelConductor( silverEta, silverK) );

	std::shared_ptr<LambertianBRDF> whiteDiffuseBRDF( new LambertianBRDF() );
	whiteDiffuseBRDF->albedo = RGB(1,1,1);
	std::shared_ptr<LambertianBRDF> redDiffuseBRDF( new LambertianBRDF() );
	redDiffuseBRDF->albedo = RGB(1,0,0);
	std::shared_ptr<LambertianBRDF> greenDiffuseBRDF( new LambertianBRDF() );
	greenDiffuseBRDF->albedo = RGB(0,1,0);
	std::shared_ptr<LambertianBRDF> cyanDiffuseBRDF( new LambertianBRDF() );
	cyanDiffuseBRDF->albedo = RGB(0,1,1);

	std::shared_ptr<MirrorBRDF> perfectMirrorBRDF( new MirrorBRDF( silverFresnel ) );
	std::shared_ptr<PerfectRefractionBTDF> perfectRefractionGlass( new PerfectRefractionBTDF(1.0f/1.5f) );

	std::shared_ptr<Material> whiteDiffuseMaterial( new Material());
	whiteDiffuseMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( whiteDiffuseBRDF );
	std::shared_ptr<Material> redDiffuseMaterial( new Material());
	redDiffuseMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( redDiffuseBRDF );
	std::shared_ptr<Material> greenDiffuseMaterial( new Material());
	greenDiffuseMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( greenDiffuseBRDF );
	std::shared_ptr<Material> cyanDiffuseMaterial( new Material());
	cyanDiffuseMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( cyanDiffuseBRDF );

	std::shared_ptr<Material> mirrorMaterial( new Material());
	mirrorMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( perfectMirrorBRDF );
	std::shared_ptr<Material> glassMaterial( new Material());
	glassMaterial->bxdf = std::dynamic_pointer_cast<BxDF>( perfectRefractionGlass );


    std::cout << "RayTracer v0.1" << std::endl;
    std::cout << "Rendering scene..." << std::endl;

	std::shared_ptr<BPTIlluminationSolver> solver( new BPTIlluminationSolver(8,3) );
//	std::shared_ptr<PTIlluminationSolver> solver( new PTIlluminationSolver(8) );

    SimpleCamera camera( 320, 240, 
			std::dynamic_pointer_cast<IlluminationSolver>( solver ), 
			10);

    camera.planeSize = 2.0f*glm::vec2( 6.4f, 4.8f );
    camera.focalDistance = 15.0f;
    camera.position += glm::vec3( 0,0, 135 );

    std::shared_ptr<Scene> scene( new Scene() );

    std::shared_ptr<Sphere> light( new Sphere() );
    light->center = glm::vec3( 0, 38, -20);
    light->radius = 5.0f;
    light->material->albedo = RGB(1,1,1);
    light->material->emmitance = 1.0f*RGB(1,1,1);
    light->material->power = 20.0f;

//    std::shared_ptr<Sphere> light2( new Sphere() );
//    light2->center = glm::vec3( 10, 52, -20);
//    light2->radius = 15.0f;
//    light2->material->albedo = RGB(1,1,1);
//    light2->material->emmitance = RGB(1,1,1)*5.0f;
//    light2->material->power = 30.0f;

    std::shared_ptr<Sphere> sphere1( new Sphere() );
    sphere1->center = glm::vec3( 20, -30, -10 );
    sphere1->radius = 10.0f;
	sphere1->material = glassMaterial;

    std::shared_ptr<Sphere> sphere2( new Sphere() );
    sphere2->center = glm::vec3( -20, -20, -20 );
    sphere2->radius = 20.0f;
	sphere2->material = mirrorMaterial;
    sphere2->material->albedo = RGB(1.0,1.0,1.0);
//    sphere2->material->reflectionSample = mirrorSample;
//    sphere2->material->customBRDF = mirrorBRDF;

    std::shared_ptr<Sphere> backWall( new Sphere() );
    backWall->center = glm::vec3( 0, 0, -100050 );
    backWall->radius = 100000.0f;
	backWall->material = whiteDiffuseMaterial;
    backWall->material->albedo = RGB(1,1,1);
//    backWall->material->reflectionSample = mirrorSample;
//    backWall->material->customBRDF = mirrorBRDF;

    std::shared_ptr<Sphere> frontWall( new Sphere() );
    frontWall->center = glm::vec3( 0, 0, 100100 );
    frontWall->radius = 100000.0f;
    frontWall->material->albedo = RGB(1,1,1);

    std::shared_ptr<Sphere> leftWall( new Sphere() );
    leftWall->center = glm::vec3( -100040, 0, -1000);
    leftWall->radius = 100000.0f;
	leftWall->material = redDiffuseMaterial;
    leftWall->material->albedo = RGB(1.0,0.0,0.0);

    std::shared_ptr<Sphere> rightWall( new Sphere() );
    rightWall->center = glm::vec3( 100040, 0, -1000);
    rightWall->radius = 100000.0f;
	rightWall->material = greenDiffuseMaterial;
    rightWall->material->albedo = RGB(0.0,1.0,0.0);

    std::shared_ptr<Sphere> roof( new Sphere() );
    roof->center = glm::vec3( 0, 100040, 0);
    roof->radius = 100000.0f;
	roof->material = whiteDiffuseMaterial;
    roof->material->albedo = RGB(1,1,1);

    std::shared_ptr<Sphere> almostPlane( new Sphere() );
    almostPlane->center = glm::vec3( 0, -100040, 0 );
    almostPlane->radius = 100000.0f;
	almostPlane->material = whiteDiffuseMaterial;
    almostPlane->material->albedo = RGB(1,1,1);

    scene->addObject( std::dynamic_pointer_cast<Object>(sphere1) );
    scene->addObject( std::dynamic_pointer_cast<Object>(sphere2) );
    scene->addObject( std::dynamic_pointer_cast<Object>(backWall) );
    scene->addObject( std::dynamic_pointer_cast<Object>(leftWall) );
    scene->addObject( std::dynamic_pointer_cast<Object>(rightWall) );
//    scene->addObject( std::dynamic_pointer_cast<Object>(frontWall) );
    scene->addObject( std::dynamic_pointer_cast<Object>(roof) );
    scene->addObject( std::dynamic_pointer_cast<Object>(light) );
//    scene->addObject( std::dynamic_pointer_cast<Object>(light2) );
    scene->addObject( std::dynamic_pointer_cast<Object>(almostPlane) );

    camera.render( *scene );

    ImageWriter imWriter( camera.image );
    imWriter.writeOnPPM( filename );

    std::cout << "Done. Viewing image..." << std::endl;
    system( ("eog " + filename).c_str());

    return 0;
}
