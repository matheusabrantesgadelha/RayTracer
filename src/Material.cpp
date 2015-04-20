#include "Material.hpp"

glm::vec3 diffuseBRDF(const glm::vec3 _normal, const glm::vec3 _light)
{
    glm::vec3 randomVec = glm::sphericalRand(1.0f);
    glm::vec3 diffuseOut = glm::dot(randomVec,_normal) < 0 ? -randomVec : randomVec;

    return diffuseOut;
}

Material::Material()
    :diffuseColor( RGB(0,0,0) ), specularColor( RGB(1,1,1) ),
    luminosity(RGB(0,0,0)), power(3), shininess( 5.0f ), reflectiveness( 0.1 )
{
    func_brdf = diffuseBRDF;
}

Material::~Material(){}

RGB Material::calcIllumination( const glm::vec3 _normal, const LightRay _light, const glm::vec3 _view )
{
	RGB result;
	result = glm::dot( _light.direction, _normal ) * diffuseColor * _light.color;

	glm::vec3 light_reflect = reflect( _light.direction, _normal );
	float reflect_factor = glm::dot( light_reflect, _view );
	if( reflect_factor > 0 )
	{
		reflect_factor = pow(reflect_factor, shininess);
		result += reflect_factor * specularColor;
	}

	result = glm::clamp( result, 0.0f, 1.0f );

	return result+luminosity;
}

RGB Material::combineColors( const RGB material, const RGB reflected )
{
	return material + reflectiveness*reflected;
}

glm::vec3 Material::brdf(const glm::vec3 normal, const glm::vec3 light)
{
    glm::vec3 randomVec = glm::sphericalRand(1.0f);
    glm::vec3 diffuseOut = glm::dot(randomVec,normal) < 0 ? -randomVec : randomVec;

    return diffuseOut;
}
