#include "DirectIlluminationSolver.hpp"

DirectIlluminationSolver::DirectIlluminationSolver(){}

DirectIlluminationSolver::~DirectIlluminationSolver(){}

RGB DirectIlluminationSolver::estimateRadiance( const Ray _ray, const Scene& _scene )
{
	return RGB(0,0,0);
}
