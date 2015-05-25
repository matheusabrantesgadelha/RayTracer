#include "Scene.hpp"

Scene::Scene() :
    environmentColor(0,0,0),
//    environmentColor(0.2,0.2,0.15),
    lightPathSize(3),
    cameraPathSize(3)
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

    if( glm::length(_obj->material->emmitance) > 0.0001f )
        lights.push_back( _obj );

}


std::shared_ptr<Scene> Scene::getptr()
{
    return shared_from_this();
}

bool Scene::intersect( Ray _ray, RayHit& _hit )
{
    bool firstHit = true;
    RayHit hitDesc;
    float distanceFromHit = 0.0f;
    for( auto o : objects )
    {
        if( o->intersect( _ray, _hit ) )
        {
            if( firstHit )
            {
                hitDesc = _hit;
                hitDesc.objId = o->id;
                hitDesc.distance = distanceFromHit = glm::length( hitDesc.position - _ray.origin );
                hitDesc.material = o->material;
                hitDesc.obj = o;
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
                    hitDesc.obj = o;
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

void Scene::computeCameraPath(Ray _orgRay, std::vector<RayHit> &_path, unsigned int _bounces)
{
    Ray ray = _orgRay;
    for( unsigned int i=0; i<_bounces; ++i )
    {
        RayHit newHit;
        if(intersect( ray, newHit ))
        {
            newHit.inDirection = ray.direction;
            glm::vec3 normal = -newHit.obj->getNormalAt( newHit.position );

            Ray newRay;
            newRay.origin = newHit.position;
            newRay.direction = newHit.material->reflectionSample( normal, ray.direction );

            float cosTheta = std::abs(glm::dot(normal, newRay.direction));
            newHit.brdf = newHit.material->BRDF( newHit.inDirection, newRay.direction, normal );
            newHit.geoTerm = cosTheta*newHit.material->BRDF( newHit.inDirection, newRay.direction, normal );
            if( newHit.obj->isLight() )  newHit.geoTerm = newHit.material->emmitance * newHit.material->power;

            if( _path.size() > 0)
            {
                newHit.geoTerm *= _path[i-1].geoTerm;
            }

            ray = newRay;

            _path.push_back( newHit );
        }
        else
        {
            break;
        }
    }
}

void Scene::computeLightPath(Ray _orgRay, std::vector<RayHit>& _path, unsigned int _bounces)
{
    Ray ray = _orgRay;
    for( unsigned int i=0; i<_bounces; ++i )
    {
        RayHit newHit;
        if(intersect( ray, newHit ))
        {
            newHit.inDirection = ray.direction;

            glm::vec3 surfNormal = -newHit.obj->getNormalAt( newHit.position );
            float cosTheta = std::max(glm::dot( ray.direction, surfNormal ),0.0f);
            newHit.incomingRadiance = cosTheta *
                                      (_path[i].material->BRDF( _path[i].inDirection, ray.direction, surfNormal ) * _path[i].incomingRadiance
                                       + _path[i].material->emmitance *_path[i].material->power);

            _path.push_back( newHit );

            Ray newRay;
            newRay.origin = newHit.position;
            newRay.direction = newHit.material->reflectionSample(
                                   newHit.obj->getNormalAt( newHit.position ),
                                   ray.direction );
            ray = newRay;
        }
        else
        {
            break;
        }
    }
}

RGB Scene::bidirectionalPathCast(Ray _ray)
{
    std::vector<RayHit> cameraHits;
    std::vector< std::vector<RayHit> > lightHits;

    for( auto light : lights)
    {
        for( unsigned int i=0; i<1; i++)
        {
            std::vector<RayHit> lightPath;
            RayHit orgHit;
            orgHit.incomingRadiance = light->material->emmitance;
            orgHit.irradiance = light->material->emmitance;
            orgHit.position = light->getRandomSurfacePoint();
            orgHit.objId = light->id;
            orgHit.material = light->material;

            lightPath.push_back(orgHit);

            Ray initialRay;
            initialRay.origin = orgHit.position ;
            initialRay.direction = glm::normalize(initialRay.origin - light->center);
            computeLightPath( initialRay, lightPath, lightBounces );

            lightHits.push_back(lightPath);
        }
    }

    computeCameraPath( _ray, cameraHits, lightBounces );

    RGB finalColor = RGB(0,0,0);
    RGB numFactors(0,0,0);

    Ray shadowRay;

    for( auto cameraHit : cameraHits )
    {

        for( auto lightPath : lightHits )
        {
            for( auto lightHit : lightPath )
            {

                shadowRay.origin = cameraHit.position;
                shadowRay.direction = glm::normalize( lightHit.position - shadowRay.origin );

                glm::vec3 normal = cameraHit.obj->getNormalAt(cameraHit.position);
                numFactors += cameraHit.material->BRDF( cameraHit.inDirection, shadowRay.direction, normal);

                RayHit shadowHit;

                if( intersect(shadowRay,shadowHit) && shadowHit.obj == lightHit.obj )
                {
                    float cosTheta = std::max(glm::dot(shadowRay.direction, normal),0.0f);
                    finalColor += lightHit.material->BRDF( lightHit.inDirection, shadowRay.direction, normal)
                                  * cameraHit.geoTerm * cosTheta * lightHit.incomingRadiance;
                }
//                std::cout << "cameraHit.brdf: " << cameraHit.brdf.r << " " << cameraHit.brdf.g << " " << cameraHit.brdf.b << std::endl;

            }
        }
    }
    //std::cout << "finalColor: " << finalColor.r << " " << finalColor.g << " " << finalColor.b << std::endl;

    return finalColor/numFactors;
}

RGB Scene::pathCast( Ray _ray )
{
    return bidirectionalPathCast( _ray);
}
