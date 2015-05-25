#ifndef ILLUMINATIONSOLVER_H_ 
#define ILLUMINATIONSOLVER_H_ 

#include "aliases.hpp"
#include "Scene.hpp"

class IlluminationSolver
{
	virtual void preProcessScene( const Scene& _scene );
	virtual RGB estimateRadiance( const Ray _ray, const Scene& _scene ) = 0;
};

#endif
