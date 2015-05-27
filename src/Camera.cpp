#include "Camera.hpp"

Camera::Camera(const unsigned int _res_width, const unsigned int _res_height, 
			const std::shared_ptr<IlluminationSolver> _solver ):
    position(0,0,0), lookAt(0,0,-1), up(0,1,0),
    resolution(_res_width, _res_height),
    planeSize( _res_width, _res_height ),
    focalDistance( 1.0f ),
    image( _res_width, _res_height ),
    rays( _res_height, std::vector<Ray>( _res_width, Ray() ) ),
	solver( _solver )
{
    aspect = (float) _res_width / (float) _res_height;
}

Camera::~Camera()
{
}

void Camera::buildRays()
{
    glm::vec3 sideVec = glm::normalize( glm::cross( lookAt, up ) );
    glm::vec2 pixelSize = glm::vec2( planeSize.x/ (float)resolution.x, planeSize.y/ (float) resolution.y );
    for( unsigned int i=0; i< rays.size(); ++i )
    {
        for( unsigned int j=0; j<rays[i].size(); ++j )
        {
            rays[i][j].origin =
                sideVec*((pixelSize.x * j)-planeSize.x/2.0f) - up*((pixelSize.y * i)-planeSize.y/2.0f)
                + position + focalDistance * lookAt;
            rays[i][j].direction = glm::normalize( rays[i][j].origin - position );
        }
    }
}

