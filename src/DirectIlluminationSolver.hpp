#ifndef DIRECTILLUMINATIONSOLVER_H_ 
#define DIRECTILLUMINATIONSOLVER_H_ 

#include "IlluminationSolver.hpp"
#include "aliases.hpp"
#include "DiffGeomData.hpp"

class DirectIlluminationSolver : public IlluminationSolver
{
public:
	DirectIlluminationSolver();
	~DirectIlluminationSolver();

	virtual void estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples );
	
	static bool lightContribution( std::shared_ptr<Object> _fromObj,
		std::shared_ptr<Object> _light, Ray _ray, std::tuple<RGB, float>& _result, 
		const Scene& _scene );
};

#endif
