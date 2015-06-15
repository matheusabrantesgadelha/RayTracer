#ifndef MIRRORBRDF_H_ 
#define MIRRORBRDF_H_ 

#include "BxDF.hpp"

class MirrorBRDF : public BxDF
{
	virtual void sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf );
	virtual bool isDelta();
};

#endif
