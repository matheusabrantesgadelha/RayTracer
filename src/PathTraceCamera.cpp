#include "PathTraceCamera.hpp"

PathTraceCamera::PathTraceCamera(const unsigned int _res_width, const unsigned int _res_height, const unsigned int _ns)
    : Camera( _res_width, _res_height ), numSamples( _ns ), bounces( 3 ), deltaDisplacement( 0.1f)
{
}

PathTraceCamera::~PathTraceCamera()
{
}

void PathTraceCamera::render(Scene _scene)
{
	buildRays();
    int numPixesl = rays.size() * rays[0].size();
    int pixelsDone = 0;
    _scene.setLightBounces( this->bounces );

    glm::vec3 sideVec = glm::normalize( glm::cross( lookAt, up ));

    for( unsigned int i=0; i < rays.size(); ++i )
	{
		for( unsigned int j=0; j < rays[i].size(); ++j )
		{
            RGB colorSum = RGB(0.0f);
			for( unsigned int s = 0; s<numSamples; ++s ){
                glm::vec2 randomDisp = glm::diskRand(deltaDisplacement);
                glm::vec3 displacementVec = randomDisp.x * sideVec + randomDisp.y * up;

                Ray displacedRay = rays[i][j];
                displacedRay.origin += displacementVec;

				RayHit hit;
                colorSum += _scene.pathCast( displacedRay, hit, bounces );
			}
            image.data[i][j] = glm::clamp(colorSum / (float)numSamples, 0.0f, 1.0f);
            pixelsDone++;
            printf("Rendering... Completed: %.2f%%\n", pixelsDone*100.0f /(float) numPixesl);
		}
	}
}

