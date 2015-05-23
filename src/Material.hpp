#ifndef  MATERIAL_H
#define  MATERIAL_H

#include <iostream>
#include <cmath>
#include <functional>

#include "gtc/random.hpp"
#include "gtc/constants.hpp"

#include "aliases.hpp"

glm::vec3 diffuseSampling( const glm::vec3 _normal, const glm::vec3 _light );

RGB diffuseBRDF(const glm::vec3 _in, const glm::vec3 _out, const glm::vec3 _normal,  Material _m);

const float POW_PI_MINUS_1 = 1.0f/glm::pi<float>();

/**
 * @brief The Material class. Represents a material.
 */
class Material
{
public:
    /**
     * @brief Material constructor
     */
    Material ();
    ~Material();

    /**
     * @brief brdf Returns an outgoing light considering brdf
     * @param normal Normal of the surface
     * @param light Light direction of incoming light
     * @return Outgoing light direction
     */
    std::function< RGB( const glm::vec3, const glm::vec3, const glm::vec3, Material ) > customBRDF;

    RGB BRDF( const glm::vec3, const glm::vec3, const glm::vec3 );

    std::function< glm::vec3( const glm::vec3, const glm::vec3 ) > reflectionSample;

    /**
     * @brief diffuseColor Diffuse color of the surface
     */
    RGB albedo;
    /**
     * @brief specularColor Specular color of the surface
     */
    RGB specularColor;
    /**
     * @brief luminosity Light emission of the surface
     */
    RGB emmitance;
    /**
     * @brief power Power of the emitted light
     */
    float power;
    /**
     * @brief shininess Shininess component of the phong surface
     */
    float shininess;
    /**
     * @brief reflectiveness Self-explained
     */
    float reflectiveness;
};

#endif
