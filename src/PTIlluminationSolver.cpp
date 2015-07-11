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

			if( std::get<1>(sample) > 0.0f ){
				_samples.push_back( sample );
			}
			pathPDF *= hit.pdf;
			pathThroughput *= hit.throughput;
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
	RGB cumulativeThroughput = RGB(1,1,1);
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
			cumulativeThroughput *= _path.back().throughput;

			if( _path.size() > 4 )
			{
				float q = maxRadiance( cumulativeThroughput );
				if( !russianRoulette( q ) ) break;
				_path.back().throughput = (cosTheta * bxdfResult)/ q;
			}

			currentRay.origin = hit.position;
			currentRay.direction = out;
		}
		else break;
	}
}

bool PTIlluminationSolver::russianRoulette( float _probability )
{
	if(glm::linearRand(0.0f,1.0f) < _probability) return true;
	else return false;
}

float PTIlluminationSolver::maxRadiance( RGB _radiance )
{
	if( _radiance.r >= _radiance.g && _radiance.r >= _radiance.b )
		return _radiance.r;
	if( _radiance.g >= _radiance.r && _radiance.g >= _radiance.b )
		return _radiance.g;
	return _radiance.b;
}

