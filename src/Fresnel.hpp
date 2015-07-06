#ifndef FRESNEL_H_ 
#define FRESNEL_H_ 

#include "aliases.hpp"

class Fresnel
{
public:
	virtual RGB evaluate( const float _cosi ) = 0;
};

class NoFresnel : public Fresnel
{
public:
	NoFresnel();
	~NoFresnel();
	virtual RGB evaluate( const float _cosi );
	static std::shared_ptr<Fresnel> getInstance();
private:
	static std::shared_ptr<NoFresnel> instance;
};

#endif
