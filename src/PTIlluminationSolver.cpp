#include "PTIlluminationSolver.hpp"

PTIlluminationSolver::PTIlluminationSolver()
{
}

PTIlluminationSolver::~PTIlluminationSolver()
{
}

void PTIlluminationSolver::estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples )
{
}

void PTIlluminationSolver::buildPath( 
		const unsigned int _pathSize, 
		const Ray _startRay, 
		const Scene& _scene,
		std::list< RayHit >& _path )
{
	Ray currentRay = _startRay;
	for( unsigned int i=0; i<_pathSize; ++i )
	{
		RayHit hit;
		if( _scene.intersect( currentRay, hit ) )
		{
			_path.push_back( hit );
			if( hit.obj->isLight() ) break;
			currentRay.origin = hit.position;
			DiffGeoData geo = hit.obj->getDiffGeoDataAtPoint( hit.position );
			glm::vec3 in = currentRay.direction;
		}
		else break;
	}
}
