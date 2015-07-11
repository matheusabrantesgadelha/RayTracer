#ifndef FRESNELDIELETRIC_H_ 
#define FRESNELDIELETRIC_H_ 

#include <algorithm>
#include "Fresnel.hpp"

class FresnelDieletric : public Fresnel
{
public:
	FresnelDieletric( const float _etai, const float _etat );
	virtual RGB evaluate( const float _cosi );
private:
	float etai;
	float etat;
};

#endif
