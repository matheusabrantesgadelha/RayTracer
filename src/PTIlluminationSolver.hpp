 
#ifndef PTILLUMINATIONSOLVER_H_ 
#define PTILLUMINATIONSOLVER_H_ 

#include "DirectIlluminationSolver.hpp"
#include <list>

class PTIlluminationSolver : public IlluminationSolver
{
	PTIlluminationSolver();
	~PTIlluminationSolver();

	virtual void estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples );

	static void buildPath( unsigned int _pathSize, 
			const Ray _startRay, 
			const Scene& _scene,
			std::list< RayHit >& _path );
};

#endif
