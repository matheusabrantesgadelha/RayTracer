#ifndef  MATERIAL_H
#define  MATERIAL_H

#include <iostream>
#include <cmath>

#include "aliases.hpp"

class Material
{
	public:
		Material ();
		~Material();
		RGB calcIllumination( const glm::vec3 _normal, const LightRay _light, const glm::vec3 _view );
		RGB combineColors( const RGB material, const RGB reflected );
		
		RGB diffuseColor;
		RGB specularColor;
		RGB luminosity;
		float shininess;
		float reflectiveness;
};

#endif
