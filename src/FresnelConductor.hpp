#ifndef FRESNELCONDUCTOR_H_ 
#define FRESNELCONDUCTOR_H_ 

#include "Fresnel.hpp"

class FresnelConductor : public Fresnel
{
public:
	FresnelConductor( const float _eta, const float _k );
	virtual RGB evaluate( const float _cosi );
private:
	float eta;
	float k;
};

#endif
