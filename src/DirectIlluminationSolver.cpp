#include "DirectIlluminationSolver.hpp"

DirectIlluminationSolver::DirectIlluminationSolver(){}

DirectIlluminationSolver::~DirectIlluminationSolver(){}

void DirectIlluminationSolver::estimateRadiance( Ray _ray, const Scene& _scene, 
		std::vector< std::tuple<RGB, float> >& _samples )
{
	RayHit hit;
	if( _scene.intersect( _ray, hit ) )
	{
		if( hit.obj->isLight() ) 
		{
			_samples.push_back( std::make_tuple( hit.obj->material->emmitance, 1.0f));
			return ;
		}

		for( auto lightObj : _scene.lights )
		{
			Ray shadowRay;
			shadowRay.origin = hit.position;
			std::tuple<RGB,float> sample;
			lightContribution( hit.obj, lightObj, shadowRay, sample, _scene  );
			_samples.push_back( sample );
		}
	}
	else
	{
		_samples.push_back( std::make_tuple( RGB(0,0,0), 1.0f ) );
	}
}

bool DirectIlluminationSolver::lightContribution( std::shared_ptr<Object> _fromObj,
		std::shared_ptr<Object> _light, Ray _ray, std::tuple<RGB, float>& _result, 
		const Scene& _scene )
{
	float pdf=1.0f;
	DiffGeoData sampleLightGeo = _light->getSampledDiffGeoData(pdf);
	
	_ray.direction = glm::normalize( sampleLightGeo.point - _ray.origin );
	RayHit lightHit;

	if( _scene.intersect( _ray, lightHit ) )
	{
		if (glm::length(lightHit.position - sampleLightGeo.point ) < 0.00001f)
		{
			DiffGeoData geo = _fromObj->getDiffGeoDataAtPoint( _ray.origin );
			float cosTheta = AbsDot(geo.normal, _ray.direction);

			RGB radiance = _fromObj->material->bxdf->radiance( geo, _ray.direction, 
					_ray.direction ) * lightHit.obj->material->emmitance;

			radiance *= cosTheta;

			pdf = glm::length2( _ray.origin - sampleLightGeo.point ) /
					( AbsDot( sampleLightGeo.normal, _ray.direction ) 
					  * _light->getArea() );

			_result = std::make_tuple( radiance, pdf );
			return true;
		}
		else
		{
			_result = std::make_tuple( RGB(0,0,0), pdf );
			return false;
		}
	}
	else
	{
		_result = std::make_tuple( RGB(0,0,0), pdf );
		return false;
	}
}
