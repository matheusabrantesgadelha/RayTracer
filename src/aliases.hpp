#ifndef ALIASES_H_
#define ALIASES_H_

#include <vector>
#include <memory>

#include "glm.hpp"

typedef glm::vec3 RGB;
typedef glm::vec4 RGBA; 

struct Ray
{
	Ray( glm::vec3 _origin = glm::vec3(0,0,0), glm::vec3 _direction = glm::vec3(0,0,0) )
		: origin( _origin ), direction( _direction ){}
	glm::vec3 origin;
	glm::vec3 direction;
};

struct RayHit
{
	glm::vec3 position;
	RGB color;
	RGB luminosity;
    float distance;
	unsigned int objId;
};

struct LightRay
{
	LightRay( RGB _color = RGB(0,0,0), glm::vec3 _direction = glm::vec3(0,0,0))
		: color( _color ), direction( _direction ){}
	RGB color;
	glm::vec3 direction;
};

#endif
