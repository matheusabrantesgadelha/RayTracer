#ifndef MIRRORBRDF_H_ 
#define MIRRORBRDF_H_ 

#include "BxDF.hpp"
#include "FresnelConductor.hpp"

class MirrorBRDF : public BxDF
{
public:
	MirrorBRDF();
	MirrorBRDF( std::shared_ptr<FresnelConductor> _fresnel );
	virtual RGB sample( const DiffGeoData _geoData, const glm::vec3 _in, glm::vec3& _out, float& _pdf );
	virtual RGB radiance( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out );
	virtual float pdf( const DiffGeoData _geoData, const glm::vec3 _in, const glm::vec3 _out );
	virtual bool isDelta();
};

#endif
