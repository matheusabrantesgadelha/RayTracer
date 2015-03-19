#include "Object.hpp"

RGB Object::computeLight( const glm::vec3 _pos, const glm::vec3 _view )
{
	LightRay light;
	RGB finalColor (0,0,0);

	for( auto o : scene->objects )
	{
		if( glm::length(o->material.luminosity) >= 0.00001 && o->id != this->id )
		{
			RayHit hit;
			glm::vec3 ray_dir(glm::normalize( o->center-_pos ));
			Ray ray( _pos, ray_dir );
			if( scene->rayCast( ray, hit ) )
			{
				if( hit.objId == o->id )
				{
					light.color = o->material.luminosity;
					light.direction = ray_dir; 
					finalColor += material.calcIllumination( getNormalAt( _pos ), light, _view );
				}
			}
		}
	}
	return finalColor;
}

RGB Object::computeReflection( const glm::vec3 _pos, const glm::vec3 _view )
{
	LightRay light;
	RGB finalColor (0,0,0);

	for( auto o : scene->objects )
	{
		RayHit hit;
		glm::vec3 normal = getNormalAt( _pos );
		glm::vec3 ray_dir(glm::reflect( _view, normal));
		Ray ray( _pos, ray_dir );
		if( scene->rayCast( ray, hit ) )
		{
			finalColor = o->computeLight( hit.position, ray.direction ) 
				* std::min( 1.0f, 1.0f/glm::length( hit.position - _pos)) ;
		}
	}
	return finalColor;
}
