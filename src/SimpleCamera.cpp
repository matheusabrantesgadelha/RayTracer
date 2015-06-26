#include "SimpleCamera.hpp"

SimpleCamera::SimpleCamera(  const unsigned int _res_width, const unsigned int _res_height,
		const std::shared_ptr<IlluminationSolver> _solver, const unsigned int _nSamples ) :
	Camera( _res_width, _res_height, _solver ),
	samples( _nSamples )
{}

void SimpleCamera::render( Scene& _scene )
{
	buildRays();
	for( size_t i=0; i<rays.size(); ++i )
		for( size_t j=0; j<rays[i].size(); ++j )
		{
			std::vector< std::tuple<RGB,float> > samples;
			for( size_t s=0; s<100; ++s )
				solver->estimateRadiance( rays[i][j], _scene, samples );

			RGB finalColor;

			for( size_t s=0; s<samples.size(); ++s)
			{
				finalColor += std::get<0>( samples[s] ) / std::get<1>( samples[s] );
			}
//			std::cout << finalColor.r << " " << finalColor.g << " " << finalColor.b << std::endl;
			finalColor *= 1.0f/(float) samples.size();

			image.data[i][j] = finalColor;
		}
}
