#include "FresnelDieletric.hpp"

FresnelDieletric::FresnelDieletric( const float _etai, const float _etat )
	: etai( _etai ), etat( _etat ){}

RGB FresnelDieletric::evaluate( const float _cosi )
{
	float cosi = glm::clamp( _cosi, -1.f, 1.f );
	bool entering = cosi > 0;
	float ei = etai, et = etat;
	if( !entering ) std::swap( ei, et );

	float sint = ei/et * sqrtf( std::max( 0.f, 1.f - cosi*cosi ));
	if( sint>1.f ) return RGB(1.f);
	else
	{
		float cost = sqrtf( std::max( 0.f, 1.f - sint*sint ));
		
		float Rpar = ((etat*cosi) - (etai*cost))/
					 ((etat*cosi) + (etai*cost));
		float Rper = ((etai*cosi) - (etat*cost))/
					 ((etai*cosi) + (etat*cost));
		return RGB( Rpar*Rpar + Rper*Rper )/2.f;
	}
}

