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

RGB Material::BRDF(const glm::vec3 _in, const glm::vec3 _out, const glm::vec3 _normal )
{
    return customBRDF( _in, _out, _normal, *this );
}
