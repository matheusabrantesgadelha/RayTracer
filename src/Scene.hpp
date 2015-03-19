#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>

#include "glm.hpp"
#include "aliases.hpp"
#include "Object.hpp"

class Object;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene();
	~Scene();
	std::shared_ptr<Scene> getptr();
	void addObject( std::shared_ptr<Object> _obj );
	bool rayCast( Ray _ray, RayHit& _hit);
	bool finalRayCast( Ray _ray, RayHit& _hit);

	std::vector< std::shared_ptr<Object> > objects;
	
};

#endif

