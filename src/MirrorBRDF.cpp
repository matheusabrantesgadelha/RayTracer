#include "MirrorBRDF.hpp"

void MirrorBRDF::sample( DiffGeoData _geoData, glm::vec3 _in, glm::vec3& _out, float& _pdf )
{
	glm::vec3 reflected = glm::reflect( -_in, _geoData.normal);
	_out = reflected;
	_pdf = pdf( _geoData, _in, _out ) ;

	return ;
}


float MirrorBRDF::pdf( DiffGeoData _geoData, glm::vec3 _in, glm::vec3 _out )
{
	glm::vec3 reflected = glm::reflect( -_in, _geoData.normal);
	std::cout << glm::dot(reflected, _out) << std::endl;
	if(glm::dot( reflected, _out ) - 1.0f < 0.0001f ) return 1.0f;
	else return 0.0f;
}

bool MirrorBRDF::isDelta(){ 
	return true; 
}
