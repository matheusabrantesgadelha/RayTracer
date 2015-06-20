#ifndef ALIASES_H_
#define ALIASES_H_

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "glm.hpp"
#include "gtc/constants.hpp"
#include "gtx/norm.hpp"

//#include "Material.hpp"

const float PI = glm::pi<float>();
const float INV_PI = 1.0f/glm::pi<float>();
const float TWO_PI = 2.0f*PI;

typedef glm::vec3 RGB;
typedef glm::vec4 RGBA;

class Material;
class Object;

struct Ray
{
    Ray( glm::vec3 _origin = glm::vec3(0,0,0), glm::vec3 _direction = glm::vec3(0,0,0) )
        : origin( _origin ), direction( _direction ) {}
    glm::vec3 origin;
    glm::vec3 direction;
};

struct RayHit
{
    glm::vec3 position;
    RGB color;
    RGB luminosity;
    RGB incomingRadiance;
    RGB irradiance;
    glm::vec3 geoTerm;
    glm::vec3 inDirection;
    glm::vec3 brdf;
    float distance;
    unsigned int objId;
    std::shared_ptr<Material> material;
    std::shared_ptr<Object> obj;
};

struct LightRay
{
    LightRay( RGB _color = RGB(0,0,0), glm::vec3 _direction = glm::vec3(0,0,0))
        : color( _color ), direction( _direction ) {}
    RGB color;
    glm::vec3 direction;
};

inline float AbsDot( glm::vec3 a, glm::vec3 b )
{
	float val = glm::dot(a,b);
	if ( val < 0.0f ) return -val;
	return val;
}

inline void PrintVec( glm::vec3 v )
{
	std::cout << v.r << " " << v.g << " " << v.b << std::endl;
}

#endif
