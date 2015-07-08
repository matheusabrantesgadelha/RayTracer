#include "FresnelConductor.hpp"

FresnelConductor::FresnelConductor( const RGB _eta, const RGB _k ) :
	eta( _eta ), k( _k )
{
}

RGB FresnelConductor::evaluate( const float _cosi )
{
	RGB tmp = (eta*eta + k*k) * _cosi*_cosi;
	RGB Rpar2 = (tmp - (2.f*eta*_cosi) + RGB(1,1,1))/
		(tmp - (2.f*eta*_cosi) + RGB(1,1,1));
	RGB tmp2 = eta*eta + k*k;
	RGB Rperp2 = (tmp2 - (2.f * eta * _cosi) + RGB(_cosi,_cosi,_cosi))/
		(tmp2 + (2.f * eta * _cosi) + RGB(_cosi,_cosi,_cosi));
	return (Rpar2 + Rperp2)/2.f;
}
