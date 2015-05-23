#ifndef DIFFGEODATA_H
#define DIFFGEODATA_H

#include <memory>

#include <glm.hpp>
#include "Object.hpp"

struct DiffGeoData
{
	DiffGeoData( const glm::vec3 _normal = glm::vec3(), const glm::vec3 _du = glm::vec3(), 
			const glm::vec3 _dv = glm::vec3(), const std::shared_ptr<Object> _object = nullptr ):
		normal( _normal ), du( _du ), dv( _dv ), object( _object )
	{}

	glm::vec3 normal;
	glm::vec3 point;
	glm::vec3 du;
	glm::vec3 dv;

	std::shared_ptr<Object> object;
};

#endif
