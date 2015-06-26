#include "PTIlluminationSolver.hpp"

PTIlluminationSolver::PTIlluminationSolver(unsigned int _pathSize):
	pathSize( _pathSize )
{
}

PTIlluminationSolver::~PTIlluminationSolver()
{
}

void PTIlluminationSolver::estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples )
{
	std::list<RayHit> path;
	buildPath( pathSize, _ray, _scene, path );

	for( auto light : _scene.lights )
	{
		float pathPDF = 1.0f;
		RGB pathThroughput = RGB(1,1,1);
		RGB pathRadiance;
		for( auto hitIter = path.begin(); hitIter != path.end(); ++hitIter )
		{
			RayHit hit = *hitIter;
			std::tuple<RGB,float> sample;
			DirectIlluminationSolver::lightContribution(
					hit.obj, light, hit.position, sample, _scene );
			std::get<0>(sample) *= pathThroughput;
			std::get<1>(sample) *= pathPDF;
			
			_samples.push_back( sample );

			pathThroughput *= hit.throughput;
			pathPDF *= hit.pdf;
		}
	}
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

			DiffGeoData geo = hit.obj->getDiffGeoDataAtPoint( hit.position );
			glm::vec3 in = currentRay.direction;
			glm::vec3 out;
			float pdf;

			RGB bxdfResult = hit.obj->material->bxdf->sample( geo, in, out, pdf );
			float cosTheta = AbsDot( in, out );
			_path.back().pdf = pdf;
			_path.back().throughput = cosTheta * bxdfResult;

			currentRay.origin = hit.position;
			currentRay.direction = out;
		}
		else break;
	}
}
