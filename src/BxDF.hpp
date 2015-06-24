#ifndef BXDF_H_ 
#define BXDF_H_ 

#include "aliases.hpp"
#include "DiffGeomData.hpp"

struct DiffGeoData;

class BxDF
{
public:
	virtual RGB sample( const DiffGeoData _geoData, const glm::vec3 _in, glm::vec3& _out, float& _pdf ) = 0;
	virtual RGB radiance( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out ) = 0;
	virtual float pdf( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out ) = 0;
	virtual bool isDelta();
};

#endif
