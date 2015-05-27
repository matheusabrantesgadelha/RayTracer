#ifndef DIRECTILLUMINATIONSOLVER_H_ 
#define DIRECTILLUMINATIONSOLVER_H_ 

#include "IlluminationSolver.hpp"

class DirectIlluminationSolver : public IlluminationSolver
{
public:
	DirectIlluminationSolver();
	~DirectIlluminationSolver();
	virtual RGB estimateRadiance( const Ray _ray, const Scene& _scene );
};

#endif
