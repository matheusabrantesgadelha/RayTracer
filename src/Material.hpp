#ifndef  MATERIAL_H
#define  MATERIAL_H

#include <iostream>
#include <cmath>
#include <functional>

#include "gtc/random.hpp"

#include "aliases.hpp"

glm::vec3 diffuseBRDF( const glm::vec3 _normal, const glm::vec3 _light );

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
         * @brief calcIllumination Calculates illumination in a phong-based fashion
         * @param _normal Normal of the surface where the illumination will be caculated
         * @param _light Reverse light direction
         * @param _view View vector from the camera
         * @return Final color of the surface
         */
		RGB calcIllumination( const glm::vec3 _normal, const LightRay _light, const glm::vec3 _view );

        /**
         * @brief combineColors
         * @param material
         * @param reflected
         * @return Final color after combining material color and reflected lights
         */
        RGB combineColors( const RGB material, const RGB reflected );

        /**
         * @brief brdf Returns an outgoing light considering brdf
         * @param normal Normal of the surface
         * @param light Light direction of incoming light
         * @return Outgoing light direction
         */
        glm::vec3 brdf( const glm::vec3 normal, const glm::vec3 light );

        std::function< glm::vec3( const glm::vec3, const glm::vec3 ) > func_brdf;
		
        /**
         * @brief diffuseColor Diffuse color of the surface
         */
		RGB diffuseColor;
        /**
         * @brief specularColor Specular color of the surface
         */
		RGB specularColor;
        /**
         * @brief luminosity Light emission of the surface
         */
		RGB luminosity;
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
