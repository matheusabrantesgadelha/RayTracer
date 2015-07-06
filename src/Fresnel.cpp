#include "Fresnel.hpp"

std::shared_ptr<NoFresnel> NoFresnel::instance = nullptr;

NoFresnel::NoFresnel(){}

NoFresnel::~NoFresnel(){}

RGB NoFresnel::evaluate( const float )
{
	return RGB(1,1,1);
}

std::shared_ptr<Fresnel> NoFresnel::getInstance()
{
	if( NoFresnel::instance == nullptr )
	{
		instance = std::make_shared<NoFresnel>();
	}

	return std::dynamic_pointer_cast<Fresnel>(instance);
}
