#ifndef PERFECTREFRACTIONBTDF_H_ 
#define PERFECTREFRACTIONBTDF_H_ 

#include "BxDF.hpp"

class PerfectRefractionBTDF : public BxDF
{	

public:
	PerfectRefractionBTDF( const float _refractionRatio );
	virtual RGB sample( const DiffGeoData _geoData, const glm::vec3 _in, glm::vec3& _out, float& _pdf );
	virtual RGB radiance( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out );
	virtual float pdf( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out );
	virtual bool isDelta();

private:
	float refractionRatio;
};

#endif
