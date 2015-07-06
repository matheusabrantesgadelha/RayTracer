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
	const glm::vec3 oc = center - _ray.origin;
	bool isInside = false;
	if( std::abs(glm::length( oc )-radius) <= 0.0001f )
		isInside = true;

	float tc = glm::dot(_ray.direction, oc);
	float thc, thc2, t;
	if( tc < 0 ) return false;
	else
	{
		thc2 = radius*radius - glm::length2(oc) + tc*tc;
		if( thc2 < 0 ) return false;
		else
		{
			thc = std::sqrt( thc2 );
			if( isInside )
				t = tc + thc;				
			else t = tc - thc;
			_hit.position = _ray.origin + t*_ray.direction;
			return true;
		}
	}
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
