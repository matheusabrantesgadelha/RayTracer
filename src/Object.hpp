#ifndef OBJECT_H_
#define OBJECT_H_

#include "aliases.hpp"
#include "Material.hpp"
#include "Scene.hpp"

class Scene;

class Object
{
public:
    Object();

	virtual bool rayCast( Ray _ray, RayHit& _hit ) = 0;
	virtual glm::vec3 getNormalAt( glm::vec3 _p ) = 0;
    virtual glm::vec3 getRandomSurfacePoint() = 0;
	RGB computeLight( const glm::vec3 _pos, const glm::vec3 _view );
	RGB computeReflection( const glm::vec3 _pos, const glm::vec3 _view );

	unsigned int id;
	std::shared_ptr<Scene> scene;
	//TODO: change this to child classes to treat area lights.
	glm::vec3 center;
    std::shared_ptr<Material> material;

};

#endif

