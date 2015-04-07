#include "Scene.hpp"

Scene::Scene() :
    environmentColor(0,0,0)
//    environmentColor(0.1,0.1,0.05)
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
                hitDesc.distance = distanceFromHit = glm::length( hitDesc.position - _ray.origin );
				firstHit = false;
			}
			else
			{
				if( glm::length( _ray.origin - _hit.position ) < distanceFromHit )
				{
					hitDesc = _hit;
					hitDesc.objId = o->id;
                    hitDesc.distance = distanceFromHit = glm::length( hitDesc.position - _ray.origin );
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

		return true;
	}
	
	return false;
}

RGB Scene::pathCast( Ray _ray, RayHit& _hit, unsigned int bounces )
{
    if( bounces == 0 )
	{
        return environmentColor;
    }
    if( rayCast( _ray, _hit ) )
	{
		std::shared_ptr<Object> obj = objects[_hit.objId];
        if( glm::length(obj->material.luminosity) > 0.00001 ) return obj->material.luminosity;
        //RGB emittance = obj->material.luminosity * (1.0f/_hit.distance);

        glm::vec3 randomVec = glm::sphericalRand(1.0f);
        glm::vec3 dirOnNormEmiSphere =
                glm::dot(randomVec, obj->getNormalAt(_hit.position)) > 0 ? randomVec : -randomVec ;

        Ray randomRay;
        randomRay.origin = _hit.position;
        randomRay.direction = dirOnNormEmiSphere;

        RGB lightRadiance(0,0,0);

        for( auto lightSource : objects)
        {
            if( glm::length(lightSource->material.luminosity) > 0.0001f )
            {
                Ray rayToLight;
                rayToLight.origin = _hit.position;
                rayToLight.direction = glm::normalize( lightSource->center - _hit.position );

                RayHit lightHit;

                if( rayCast( rayToLight, lightHit ) )
                {
                    if( lightHit.objId == lightSource->id )
                    {
                        lightRadiance = 2.0f * obj->material.diffuseColor *
                                glm::dot(rayToLight.direction, obj->getNormalAt(_hit.position));
                        lightRadiance *= (1.0f/lightHit.distance) * lightSource->material.power;
                    }
                }
            }
        }

        float cosTheta = glm::dot(randomRay.direction, obj->getNormalAt(_hit.position));
        RGB BRDF = 2.0f * obj->material.diffuseColor * cosTheta;

        RayHit newHit;
        RGB reflected = pathCast( randomRay, newHit, bounces-1 );
//        reflected *= 10.0f/newHit.distance;

//        lightRadiance = RGB(0,0,0);

        return glm::clamp(reflected*BRDF + 0.1f*lightRadiance,0.f,1.f);
    }
	
    return environmentColor;
}
