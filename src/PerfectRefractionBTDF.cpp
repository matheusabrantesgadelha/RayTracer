#include "PerfectRefractionBTDF.hpp"

PerfectRefractionBTDF::PerfectRefractionBTDF( const float _refractionRatio ) :
	refractionRatio( _refractionRatio )
{
	fresnel = std::make_shared<FresnelDieletric>(_refractionRatio, 1.0f/refractionRatio);
}

RGB PerfectRefractionBTDF::sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf )
{
	glm::vec3 refracted;
	bool entering = true;
	RGB F(0,0,0);
	float eta = refractionRatio;

	if( glm::dot(_geoData.normal, _in) > 0.0f)
	{
		entering = false;
		eta = 1.f/refractionRatio;
		refracted = glm::refract( _in, -_geoData.normal, 1.f/refractionRatio);
	}
	else{
		refracted = glm::refract( _in, _geoData.normal, refractionRatio);
	}
	_out = refracted;
	_pdf = 1.0f;
	float cosTheta = AbsDot( _in, _out );

	F = fresnel->evaluate( cosTheta );

	return (1.f/eta*eta)*(RGB(1)-F)/cosTheta;
}

RGB PerfectRefractionBTDF::radiance( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return RGB(0,0,0);
//	if(pdf( _geoData, _in, _out )) return RGB(1,1,1);
//	else return RGB(0,0,0);
}

float PerfectRefractionBTDF::pdf( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return 0.0f;
//	glm::vec3 reflected = glm::reflect( _in, _geoData.normal);
//	if(std::abs(glm::dot( _out, reflected )) >= 0.999f ) return 1.0f;
//	else return 0.0f;
}

bool PerfectRefractionBTDF::isDelta(){ 
	return true; 
}
