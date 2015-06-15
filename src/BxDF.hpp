#ifndef BXDF_H_ 
#define BXDF_H_ 

#include "aliases.hpp"
#include "DiffGeomData.hpp"

struct DiffGeoData;

class BxDF
{
public:
	virtual void sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf ) = 0;
	virtual bool isDelta();
};

#endif
