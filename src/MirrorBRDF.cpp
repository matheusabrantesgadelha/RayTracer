#include "MirrorBRDF.hpp"

MirrorBRDF::MirrorBRDF() : BxDF()
{
}

MirrorBRDF::MirrorBRDF( std::shared_ptr<FresnelConductor> _fresnel )
	: BxDF( std::dynamic_pointer_cast<Fresnel>(_fresnel))
{
}

RGB MirrorBRDF::sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf )
{
	glm::vec3 reflected = glm::reflect( _in, _geoData.normal);
	_out = reflected;
	_pdf = 1.0f;
	float cosTheta = AbsDot(_in,_out);

	return fresnel->evaluate(AbsDot(_in,_geoData.normal))*RGB(1,1,1)/cosTheta;
}

RGB MirrorBRDF::radiance( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return RGB(0,0,0);
//	if(pdf( _geoData, _in, _out )) return RGB(1,1,1);
//	else return RGB(0,0,0);
}

float MirrorBRDF::pdf( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return 0.0f;
//	glm::vec3 reflected = glm::reflect( _in, _geoData.normal);
//	if(std::abs(glm::dot( _out, reflected )) >= 0.999f ) return 1.0f;
//	else return 0.0f;
}

bool MirrorBRDF::isDelta(){ 
	return true; 
}
