#include "Object.hpp"

Object::Object() : material( new Material() )
{}

RGB Object::computeLight( const glm::vec3 _pos, const glm::vec3 _view )
{
    LightRay light;
    RGB finalColor (0,0,0);

    for( auto o : scene->objects )
    {
        if( glm::length(o->material->emmitance) >= 0.00001 && o->id != this->id )
        {
            RayHit hit;
            glm::vec3 ray_dir(glm::normalize( o->center-_pos ));
            Ray ray( _pos, ray_dir );
            if( scene->rayCast( ray, hit ) )
            {
                if( hit.objId == o->id )
                {
                    light.color = o->material->emmitance;
                    light.direction = ray_dir;

                    float dist_hit = glm::length( hit.position - _pos );
                    float distance_atten = 1/(pow( dist_hit, 2) + pow(dist_hit,3) + dist_hit);
                    light.color *= distance_atten;
                    light.color *= o->material->power;

                    finalColor += material->calcIllumination( getNormalAt( _pos ), light, _view );
                }
            }
        }
    }
    return finalColor + material->emmitance;
}

RGB Object::computeReflection( const glm::vec3 _pos, const glm::vec3 _view )
{
    LightRay light;
    RGB finalColor (0,0,0);

    for( auto o : scene->objects )
    {
        RayHit hit;
        glm::vec3 normal = getNormalAt( _pos );
        glm::vec3 ray_dir(glm::reflect( _view, normal));
        Ray ray( _pos, ray_dir );
        if( scene->rayCast( ray, hit ) )
        {
            finalColor = o->computeLight( hit.position, ray.direction )
                    * std::min( 1.0f, 1.0f/glm::length( hit.position - _pos)) ;
        }
    }
    return finalColor;
}

bool Object::isLight()
{
    return ( material->emmitance.r > 0.0f ||
             material->emmitance.g > 0.0f ||
             material->emmitance.b > 0.0f );
}
