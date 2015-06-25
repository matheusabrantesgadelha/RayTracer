 
#ifndef PTILLUMINATIONSOLVER_H_ 
#define PTILLUMINATIONSOLVER_H_ 

#include "IlluminationSolver.hpp"

class PTIlluminationSolver : public IlluminationSolver
{
	PTIlluminationSolver();
	~PTIlluminationSolver();

	virtual void estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples );
};

#endif
