#include "DirectIlluminationSolver.hpp"

DirectIlluminationSolver::DirectIlluminationSolver(){}

DirectIlluminationSolver::~DirectIlluminationSolver(){}

void DirectIlluminationSolver::estimateRadiance( const Ray _ray, const Scene& _scene, 
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

			glm::vec3 sampleLightPos = lightObj->getRandomSurfacePoint();
			
			shadowRay.direction = glm::normalize( sampleLightPos - shadowRay.origin );
			RayHit lightHit;
			float pdf=1.0f;

			if( _scene.intersect( shadowRay, lightHit ) )
			{
//				if (glm::length(lightHit.position - sampleLightPos ) < 0.00001f)
				if( lightHit.obj == lightObj )
				{
					std::shared_ptr<Object> obj = hit.obj;

					glm::vec3 objNormal = obj->getNormalAt( hit.position );
					float cosTheta = AbsDot(objNormal,shadowRay.direction);

					RGB radiance = obj->material->BRDF(
							shadowRay.direction, _ray.direction,
							objNormal);

					radiance *= cosTheta;

					pdf = glm::length( hit.position - sampleLightPos );
					pdf *= pdf;
					pdf /= lightObj->getArea();

					_samples.push_back( std::make_tuple( radiance, pdf ));
				}
				else
				{
					_samples.push_back( std::make_tuple( RGB(0,0,0), pdf ) );
				}
			}
			else
			{
				_samples.push_back( std::make_tuple( RGB(0,0,0), pdf ) );
			}
		}
	}
	else
	{
		_samples.push_back( std::make_tuple( RGB(0,0,0), 1.0f ) );
	}
}

