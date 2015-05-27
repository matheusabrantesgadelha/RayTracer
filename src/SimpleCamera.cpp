#include "SimpleCamera.hpp"

SimpleCamera::SimpleCamera(  const unsigned int _res_width, const unsigned int _res_height,
		const std::shared_ptr<IlluminationSolver> _solver ) :
	Camera( _res_width, _res_height, _solver )
{}

void SimpleCamera::render( Scene& _scene )
{
	buildRays();
	for( size_t i=0; i<rays.size(); ++i )
		for( size_t j=0; j<rays[i].size(); ++j )
		{
			image.data[i][j] = solver->estimateRadiance( rays[i][j], _scene );
		}
}
