#include "Sphere.hpp"

Sphere::Sphere() : Object()
{
    scene = NULL;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect( Ray _ray, RayHit& _hit )
{
    glm::vec3 origin_center = center - _ray.origin;
    if( glm::dot( origin_center, _ray.direction ) <= 0 )
        return false;

    glm::vec3 proj_ray = glm::proj( origin_center, _ray.direction );
    glm::vec3 proj_point = proj_ray + _ray.origin;
    if( glm::length( center-proj_point ) > radius )
        return false;

    float distInter = sqrt( pow(radius,2) - pow(glm::length( proj_point - center ),2) );
    float di = glm::length( proj_point - _ray.origin ) - distInter;

    glm::vec3 intersection = _ray.origin + di*_ray.direction;
    _hit.position = intersection;

    _hit.color = material->albedo;

    return true;
}

glm::vec3 Sphere::getNormalAt( glm::vec3 _p )
{
    return glm::normalize( _p - center );
}

glm::vec3 Sphere::getRandomSurfacePoint()
{
    glm::vec3 randSurf = glm::sphericalRand(this->radius);

    return randSurf + center;
}

DiffGeoData Sphere::getDiffGeoDataAtPoint( glm::vec3 _point )
{
	glm::vec3 normal = glm::normalize( _point - center );
	return DiffGeoData( normal );
}

DiffGeoData Sphere::getSampledDiffGeoData()
{
	return getDiffGeoDataAtPoint( getRandomSurfacePoint() );
}

float Sphere::getArea()
{
	return 4.0f*PI*radius*radius;
}
