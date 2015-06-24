
#include "LambertianBRDF.hpp"

RGB LambertianBRDF::sample( const DiffGeoData _geoData, const glm::vec3 , glm::vec3& _out, float& _pdf )
{
	glm::vec3 randDir = glm::sphericalRand( 1.0f );
	randDir = glm::dot( randDir, _geoData.normal ) < 0 ? -randDir : randDir;
	_out = randDir;

	_pdf = INV_PI;

	return albedo*INV_PI;
}

RGB LambertianBRDF::radiance( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return albedo*INV_PI;
}

float LambertianBRDF::pdf( const DiffGeoData , const glm::vec3 , const glm::vec3 )
{
	return INV_PI;
}

bool LambertianBRDF::isDelta()
{
	return false;
}

