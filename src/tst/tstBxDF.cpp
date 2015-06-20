#include <iostream>

#include "../MirrorBRDF.hpp"
#include "../aliases.hpp"

#include "gtc/random.hpp"
#include "gtc/constants.hpp"

int main()
{
	MirrorBRDF brdf;
	DiffGeoData geoData;

	geoData.normal = glm::sphericalRand( 1.0f );
	
	glm::vec3 in = glm::sphericalRand( 1.0f );
	in = glm::dot( geoData.normal, in) < 0.0f ? -in : in;
	PrintVec( in );
	glm::vec3 out;

	float pdf;

	brdf.sample( geoData, in, out, pdf );
	PrintVec( out );

	std::cout << pdf << std::endl;

	return 0;
}
