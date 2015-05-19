#include "Material.hpp"

glm::vec3 diffuseSampling(const glm::vec3 _normal, const glm::vec3 _light)
{
    glm::vec3 randomVec = glm::sphericalRand(1.0f);
    glm::vec3 diffuseOut = glm::dot(randomVec,_normal) < 0 ? -randomVec : randomVec;

    return diffuseOut;
}

RGB diffuseBRDF(const glm::vec3 _in, const glm::vec3 _out, const glm::vec3 _normal, Material _m)
{
    return _m.albedo * POW_PI_MINUS_1;
}

Material::Material()
    :albedo( RGB(0,0,0) ), specularColor( RGB(1,1,1) ),
     emmitance(RGB(0,0,0)), power(3), shininess( 5.0f ), reflectiveness( 0.1 )
{
    reflectionSample = diffuseSampling;
    customBRDF = diffuseBRDF;
}

Material::~Material() {}

RGB Material::calcIllumination( const glm::vec3 _normal, const LightRay _light, const glm::vec3 _view )
{
    RGB result;
    result = glm::dot( _light.direction, _normal ) * albedo * _light.color;

    glm::vec3 light_reflect = reflect( _light.direction, _normal );
    float reflect_factor = glm::dot( light_reflect, _view );
    if( reflect_factor > 0 )
    {
        reflect_factor = pow(reflect_factor, shininess);
        result += reflect_factor * specularColor;
    }

    result = glm::clamp( result, 0.0f, 1.0f );

    return result+emmitance;
}

RGB Material::combineColors( const RGB material, const RGB reflected )
{
    return material + reflectiveness*reflected;
}

RGB Material::BRDF(const glm::vec3 _in, const glm::vec3 _out, const glm::vec3 _normal )
{
    return customBRDF( _in, _out, _normal, *this );
}
