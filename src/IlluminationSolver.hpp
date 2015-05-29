#ifndef ILLUMINATIONSOLVER_H_ 
#define ILLUMINATIONSOLVER_H_ 

#include "aliases.hpp"
#include "Scene.hpp"
#include <tuple>

class Scene;

class IlluminationSolver
{
public:
	IlluminationSolver();
	virtual void preProcessScene( const Scene& _scene );
	virtual void estimateRadiance( const Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples ) = 0;
};

#endif
