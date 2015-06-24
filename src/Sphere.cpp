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
    if( glm::dot( origin_center, _ray.direction ) <= 0.0f )
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

glm::vec3 Sphere::getRandomSurfacePoint( float& _pdf )
{
    glm::vec3 randSurf = glm::sphericalRand(this->radius);
	_pdf = 1.0f/ getArea();

    return randSurf + center;
}

DiffGeoData Sphere::getDiffGeoDataAtPoint( glm::vec3 _point )
{
	glm::vec3 normal = glm::normalize( _point - center );
	DiffGeoData diffGeo( normal, _point );
	diffGeo.object = getptr();

	return diffGeo;
}

DiffGeoData Sphere::getSampledDiffGeoData( float& _pdf )
{
	return getDiffGeoDataAtPoint( getRandomSurfacePoint(_pdf) );
}

float Sphere::getArea()
{
	return 4.0f*PI*radius*radius;
}
