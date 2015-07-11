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
			lightContribution( hit.obj, lightObj, shadowRay.origin, sample, _scene  );
			_samples.push_back( sample );
		}
	}
	else
	{
		_samples.push_back( std::make_tuple( RGB(0,0,0), 1.0f ) );
	}
}

bool DirectIlluminationSolver::lightContribution( std::shared_ptr<Object> _fromObj,
		std::shared_ptr<Object> _light, glm::vec3 _fromPos, std::tuple<RGB, float>& _result, 
		const Scene& _scene )
{
	float pdf=1.0f;
	DiffGeoData sampleLightGeo = _light->getSampledDiffGeoData(pdf);
	Ray ray;
	ray.origin = _fromPos;
	
	ray.direction = glm::normalize( sampleLightGeo.point - ray.origin );
	RayHit lightHit;

	if( _fromObj == _light )
	{
		std::get<0>(_result) = _light->material->emmitance;
		std::get<1>(_result) = 1.0f;
		return false;
	}

	if( _scene.intersect( ray, lightHit ) )
	{
		if (glm::length(lightHit.position - sampleLightGeo.point ) < 0.0001f)
		{
			DiffGeoData geo = _fromObj->getDiffGeoDataAtPoint( ray.origin );
			float cosTheta = AbsDot(geo.normal, ray.direction);

			RGB radiance = _fromObj->material->bxdf->radiance( geo, ray.direction, 
					ray.direction ) * lightHit.obj->material->emmitance;

			radiance *= cosTheta;

			pdf = glm::length2( ray.origin - sampleLightGeo.point ) /
					( AbsDot( sampleLightGeo.normal, ray.direction ) 
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
