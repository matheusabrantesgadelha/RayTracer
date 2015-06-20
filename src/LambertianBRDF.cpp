
#include "LambertianBRDF.hpp"

void LambertianBRDF::sample( DiffGeoData _geoData, glm::vec3 , glm::vec3& _out, float& _pdf )
{
	glm::vec3 randDir = glm::sphericalRand( 1.0f );
	randDir = glm::dot( randDir, _geoData.normal ) < 0 ? -randDir : randDir;
	_out = randDir;

	_pdf = INV_PI;

	return ;
}

float LambertianBRDF::pdf( DiffGeoData , glm::vec3 , glm::vec3 )
{
	return INV_PI;
}

bool LambertianBRDF::isDelta()
{
	return false;
}

