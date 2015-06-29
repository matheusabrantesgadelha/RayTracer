 
#ifndef PTILLUMINATIONSOLVER_H_ 
#define PTILLUMINATIONSOLVER_H_ 

#include "DirectIlluminationSolver.hpp"
#include <list>
#include "gtc/random.hpp"

class PTIlluminationSolver : public IlluminationSolver
{
public:
	PTIlluminationSolver( unsigned int _pathSize );
	~PTIlluminationSolver();

	virtual void estimateRadiance( Ray _ray, const Scene& _scene, 
			std::vector< std::tuple<RGB, float> >& _samples );

	static void buildPath( unsigned int _pathSize, 
			const Ray _startRay, 
			const Scene& _scene,
			std::list< RayHit >& _path );
	
	static bool russianRoulette( float _probability );

	static float maxRadiance( RGB _radiance );

private:
	unsigned int pathSize;
};

#endif
