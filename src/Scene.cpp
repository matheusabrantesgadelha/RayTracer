#include "Scene.hpp"

Scene::Scene() :
//    environmentColor(0,0,0),
    environmentColor(0.1,0.1,0.05),
    lightPathSize(2),
    cameraPathSize(2)
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

    if( glm::length(_obj->material->luminosity) > 0.0001f )
        lights.push_back( _obj );
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
                hitDesc.material = o->material;
				firstHit = false;
			}
			else
			{
				if( glm::length( _ray.origin - _hit.position ) < distanceFromHit )
				{
					hitDesc = _hit;
					hitDesc.objId = o->id;
                    hitDesc.distance = distanceFromHit = glm::length( hitDesc.position - _ray.origin );
                    hitDesc.material = o->material;
                }
			}
		}
	}
	_hit = hitDesc;
	if( distanceFromHit > 0.0f ) return true;
	return false;
}

void Scene::setLightBounces(int _numBounces)
{
    this->lightBounces = _numBounces;
}

void Scene::setCameraPathSize(const unsigned int _cameraPathSize)
{
    this->cameraPathSize = _cameraPathSize;
}

void Scene::setLightPathSize(const unsigned int _lightPathSize)
{
    this->lightPathSize = _lightPathSize;
}

bool Scene::finalRayCast( Ray _ray, RayHit& _hit )
{
	if( rayCast( _ray, _hit ) )
	{
		std::shared_ptr<Object> obj = objects[_hit.objId];
		RGB materialColor = obj->computeLight( _hit.position, _ray.direction );
		RGB reflectedColor( 0,0,0 );
		
        if( obj->material->reflectiveness > 0.0f )
		{
			reflectedColor = obj->computeReflection( _hit.position, _ray.direction );
		}
        _hit.color = obj->material->combineColors( materialColor, reflectedColor );

		return true;
	}
	
	return false;
}

void Scene::computePath(Ray _orgRay, std::vector<RayHit>& _path, unsigned int _bounces, RGB _lightColor)
{
    Ray ray = _orgRay;
    RGB color = _lightColor;
    for( unsigned int i=0; i<_bounces; ++i )
    {
        RayHit newHit;
        if(rayCast( ray, newHit ))
        {
            newHit.radiance = 2.0f * //1.0f/newHit.distance *
                    std::max(glm::dot( ray.direction, -objects[newHit.objId]->getNormalAt( newHit.position ) ),0.0f) *
                    color * newHit.material->diffuseColor;

            color = newHit.radiance;

            _path.push_back( newHit );

            Ray newRay;
            newRay.origin = newHit.position;
            newRay.direction = newHit.material->brdf(
                        objects[newHit.objId]->getNormalAt( newHit.position ),
                        glm::vec3(0,0,0) );
            ray = newRay;
        }
        else
        {
            break;
        }
    }
}

RGB Scene::bidirectionalPathCast(Ray _ray, RayHit &_hit)
{
    std::vector<RayHit> cameraHits;
    std::vector< std::vector<RayHit> > lightHits;

    for( auto light : lights)
    {
        for( unsigned int i=0; i<3; i++)
        {
            std::vector<RayHit> lightPath;
            RayHit orgHit;
            orgHit.radiance = light->material->luminosity;
            orgHit.position = light->center;
            orgHit.objId = light->id;

//            lightPath.push_back(orgHit);

            Ray initialRay;
            initialRay.origin = light->getRandomSurfacePoint();
            initialRay.direction = glm::normalize(initialRay.origin - light->center);
            computePath( initialRay, lightPath, lightBounces, light->material->luminosity * light->material->power );

            lightHits.push_back(lightPath);
        }
    }

    computePath( _ray, cameraHits, lightBounces, RGB(0,0,0) );

    RGB finalColor;
    float numFactors;
    for( auto cameraHit : cameraHits )
    {
        if( glm::length(cameraHit.material->luminosity) > 0.001f )
        {
            finalColor = cameraHit.material->luminosity;
            break;
        }

        for( auto lightPath : lightHits )
        {
            for( unsigned int i=0; i<lightPath.size(); ++i )
            {
                RayHit lightHit = lightPath[i];
                numFactors += 1.0f;

                Ray shadowRay;
                shadowRay.origin = cameraHit.position;
                shadowRay.direction = glm::normalize( lightHit.position - cameraHit.position );

                RayHit shadowHit;

                if( rayCast(shadowRay, shadowHit ) && shadowHit.objId == lightHit.objId )
                {
                    glm::vec3 normal = objects[cameraHit.objId]->getNormalAt(cameraHit.position);
                    finalColor += 2.0f * //1.0f/shadowHit.distance *
                            std::max(glm::dot(shadowRay.direction, normal),0.0f) * cameraHit.material->diffuseColor * lightHit.radiance;

//                    std::cout <<"FINAL COLOR: " << finalColor.r << " " << finalColor.g << " " << finalColor.b << std::endl;
//                    std::cout <<"RADIANCE: " << lightHit.radiance.r << " " << lightHit.radiance.g << " " << lightHit.radiance.b << std::endl;
                }
            }
        }
    }

    finalColor *= 1.0f/numFactors;
    return finalColor;
}

RGB Scene::pathCast( Ray _ray, RayHit& _hit, unsigned int bounces )
{
    return bidirectionalPathCast( _ray, _hit );
//    if( bounces == 0 )
//	{
//        return environmentColor;
//    }
//    if( rayCast( _ray, _hit ) )
//	{
//		std::shared_ptr<Object> obj = objects[_hit.objId];
//        if( glm::length(obj->material->luminosity) > 0.00001 )
//        {
//            if( bounces == this->lightBounces )
//                return obj->material->luminosity * obj->material->power;
//            else
//                return obj->material->luminosity * obj->material->power;// * (1.0f/_hit.distance);
//        }
//        //RGB emittance = obj->material->luminosity * (1.0f/_hit.distance);

//        glm::vec3 randomVec = glm::sphericalRand(1.0f);
//        glm::vec3 dirOnNormEmiSphere =
//                glm::dot(randomVec, obj->getNormalAt(_hit.position)) > 0 ? randomVec : -randomVec ;

//        Ray randomRay;
//        randomRay.origin = _hit.position;
//        randomRay.direction = dirOnNormEmiSphere;

//        RGB lightRadiance(0,0,0);

//        for( auto lightSource : objects)
//        {
//            if( glm::length(lightSource->material->luminosity) > 0.0001f )
//            {
//                Ray rayToLight;
//                rayToLight.origin = _hit.position;
//                rayToLight.direction = glm::normalize( lightSource->center - _hit.position );

//                RayHit lightHit;

//                if( rayCast( rayToLight, lightHit ) )
//                {
//                    if( lightHit.objId == lightSource->id )
//                    {
//                        lightRadiance = 2.0f * obj->material->diffuseColor *
//                                glm::dot(rayToLight.direction, obj->getNormalAt(_hit.position));
//                        lightRadiance *= (1.0f/lightHit.distance);
//                    }
//                }
//            }
//        }

//        float cosTheta = glm::dot(randomRay.direction, obj->getNormalAt(_hit.position));
//        RGB BRDF = 2.0f * obj->material->diffuseColor * cosTheta;

//        RayHit newHit;
//        RGB reflected = pathCast( randomRay, newHit, bounces-1 );

////        lightRadiance = RGB(0,0,0);

//        return glm::clamp(reflected*BRDF + 1.0f*lightRadiance, 0.f, 2.f);
//    }
	
//    return environmentColor;
}
