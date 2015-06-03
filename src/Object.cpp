#include "Object.hpp"

Object::Object() : material( new Material() )
{}

std::shared_ptr<Object> Object::getptr()
{
	return shared_from_this();
}

bool Object::isLight()
{
    return ( material->emmitance.r > 0.0f ||
             material->emmitance.g > 0.0f ||
             material->emmitance.b > 0.0f );
}
