#include "PerfectRefractionBTDF.hpp"

PerfectRefractionBTDF::PerfectRefractionBTDF( const float _refractionRatio ) :
	refractionRatio( _refractionRatio )
{
}

RGB PerfectRefractionBTDF::sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf )
{
	glm::vec3 refracted;
	if( glm::dot(_geoData.normal, _in) > 0.0f)
	{
		_geoData.normal = -_geoData.normal;
		refracted = glm::refract( _in, _geoData.normal, 1.0f/refractionRatio);
	}
	else{
		refracted = glm::refract( _in, _geoData.normal, refractionRatio);
	}
	_out = refracted;
	_pdf = 1.0f;

	return RGB(1,1,1)/AbsDot(_in,_out);
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
