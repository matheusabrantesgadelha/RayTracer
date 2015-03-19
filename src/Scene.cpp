#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addObject( std::shared_ptr<Object> _obj )
{
	_obj->id = objects.size();
	_obj->scene = getptr();
	objects.push_back( _obj );
}


std::shared_ptr<Scene> Scene::getptr()
{
	return shared_from_this();
}

bool Scene::rayCast( Ray _ray, RayHit& _hit )
{
	bool firstHit = true;
	RayHit hitDesc;
	float distanceFromHit = 0.0f;
	for( auto o : objects )
	{
		if( o->rayCast( _ray, _hit ) )
		{
			if( firstHit )
			{
				hitDesc = _hit;
				hitDesc.objId = o->id;
				distanceFromHit = glm::length( hitDesc.position - _ray.origin );
				firstHit = false;
			}
			else
			{
				if( glm::length( _ray.origin - _hit.position ) < distanceFromHit )
				{
					hitDesc = _hit;
					hitDesc.objId = o->id;
					distanceFromHit = glm::length( hitDesc.position - _ray.origin );
				}
			}
		}
	}
	_hit = hitDesc;
	if( distanceFromHit > 0.0f ) return true;
	return false;
}

bool Scene::finalRayCast( Ray _ray, RayHit& _hit )
{
	if( rayCast( _ray, _hit ) )
	{
		std::shared_ptr<Object> obj = objects[_hit.objId];
		RGB materialColor = obj->computeLight( _hit.position, _ray.direction );
		RGB reflectedColor( 0,0,0 );
		
		if( obj->material.reflectiveness > 0.0f )
		{
			reflectedColor = obj->computeReflection( _hit.position, _ray.direction );
		}
		_hit.color = obj->material.combineColors( materialColor, reflectedColor );

//		std::cout << _hit.color.r << " " << _hit.color.g << " " << _hit.color.b << std::endl;
		return true;
	}
	
	return false;
}

