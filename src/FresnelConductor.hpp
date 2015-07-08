#ifndef FRESNELCONDUCTOR_H_ 
#define FRESNELCONDUCTOR_H_ 

#include "Fresnel.hpp"

class FresnelConductor : public Fresnel
{
public:
	FresnelConductor( const RGB _eta, const RGB _k );
	virtual RGB evaluate( const float _cosi );
private:
	RGB eta;
	RGB k;
};

#endif
