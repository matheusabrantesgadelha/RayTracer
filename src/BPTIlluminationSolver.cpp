#include "BPTIlluminationSolver.hpp"

BPTIlluminationSolver::BPTIlluminationSolver( 
		const unsigned short _cameraPathSize,
		const unsigned short _lightPathSize):
	cameraPathSize( _cameraPathSize ),
	lightPathSize( _lightPathSize ){}

BPTIlluminationSolver::~BPTIlluminationSolver(){}

void BPTIlluminationSolver::estimateRadiance( Ray _ray, const Scene& _scene, 
		std::vector< std::tuple<RGB, float> >& _samples )
{
	std::list<RayHit> cameraPath;
	PTIlluminationSolver::buildPath( cameraPathSize, _ray, _scene, cameraPath );

	for( auto light : _scene.lights )
	{
		RGB sourceRadiance = light->material->emmitance;
		std::list<RayHit> lightPath;
		float lightPdf;
		DiffGeoData lightGeoData = light->getSampledDiffGeoData(lightPdf);
		Ray initLightPathRay( lightGeoData.point, lightGeoData.normal );
		PTIlluminationSolver::buildPath( lightPathSize, _ray, _scene, lightPath );

		RayHit sourceHit;
		sourceHit.position = lightGeoData.point;
		sourceHit.obj = light;
		sourceHit.source = true;
		sourceHit.pdf = 1.0f;
		sourceHit.objId = light->id;
		sourceHit.throughput = RGB(1);
		sourceHit.distance = 0.f;
		sourceHit.geoData = &lightGeoData;
		lightPath.push_front( sourceHit );

		RayHit firstHit = *std::next( lightPath.begin(), 1 );
		lightPdf *= glm::length2( lightGeoData.point - firstHit.position )/
			( AbsDot( lightGeoData.normal, firstHit.inDirection )
			  * light->getArea());
		
		float cumulativePdf = lightPdf;
		RGB cumulativeThroughput = RGB(1);
		for( auto lightHit : lightPath )
		{
			cumulativePdf *= lightHit.pdf;
			cumulativeThroughput *= lightHit.throughput;

			lightHit.pdf = cumulativePdf;
			lightHit.throughput = cumulativeThroughput;
		}

		float pathPdf = 1.0f;
		RGB pathThroughput = RGB(1,1,1);
		RGB pathRadiance;
		for( auto cameraHit : cameraPath )
		{
			if( cameraHit.obj->isLight() )
			{
				std::tuple<RGB,float> sample;
				std::get<0>(sample) = cameraHit.obj->material->emmitance;
				std::get<1>(sample) = 1.0f;
				_samples.push_back( sample );
			}
			else if( !cameraHit.obj->material->bxdf->isDelta() )
			{
				for( auto lightHit : lightPath )
				{
					std::tuple<RGB,float> sample;
					RGB inRadiance = lightHit.throughput * sourceRadiance;
					if( lightHit.source )
					{
						DirectIlluminationSolver::lightContribution(
								cameraHit.obj, lightHit.obj, cameraHit.position, sample, _scene );
						std::get<0>(sample) *= pathThroughput;
						std::get<1>(sample) *= pathPdf;

						if( std::get<1>(sample) > 0.0f )
							_samples.push_back( sample );
					}
					else
					{
						if( lightHit.obj->material->bxdf->isDelta() ) continue;
						glm::vec3 shadowRayDirection = glm::normalize( 
								lightHit.position - cameraHit.position);
						Ray shadowRay( cameraHit.position, shadowRayDirection );
						RayHit shadowHit;

						if( _scene.intersect(shadowRay, shadowHit) && 
								shadowHit.obj == lightHit.obj)
						{

							DiffGeoData lHitGeo = lightHit.obj->getDiffGeoDataAtPoint( 
									lightHit.position );
							RGB radiance;
							radiance = inRadiance * lightHit.obj->material->bxdf->radiance( 
									lHitGeo, lightHit.incomingRadiance, -shadowRayDirection );
							std::get<0>(sample) = radiance * pathThroughput;
							std::get<1>(sample) = lightHit.pdf * pathPdf;
							_samples.push_back( sample );
						}
						else{
							_samples.push_back( std::make_tuple(RGB(0), lightHit.pdf * pathPdf ));
						}
					}
				}
			}
			pathPdf *= cameraHit.pdf;
			pathThroughput *= cameraHit.throughput;
		}
	}
}
