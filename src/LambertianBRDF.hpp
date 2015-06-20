#ifndef LAMBERTIANBRDF_H_ 
#define LAMBERTIANBRDF_H_ 

#include "BxDF.hpp"

class LambertianBRDF : public BxDF
{
public:
	virtual void sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf );
	virtual float pdf( DiffGeoData _geoData, glm::vec3 _in, glm::vec3 _out );
	virtual bool isDelta();
};

#endif
