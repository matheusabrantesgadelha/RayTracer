#include "BxDF.hpp"

BxDF::BxDF()
{
	fresnel = NoFresnel::getInstance();
}

BxDF::BxDF( std::shared_ptr<Fresnel> _fresnel ) : fresnel( _fresnel )
{
}

bool BxDF::isDelta(){ 
	return false; 
}
