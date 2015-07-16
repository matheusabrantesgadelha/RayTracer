#ifndef BPTILLUMINATIONSOLVER_H_ 
#define BPTILLUMINATIONSOLVER_H_ 

#include "PTIlluminationSolver.hpp"
#include <iterator>

class BPTIlluminationSolver : public IlluminationSolver
{
	public:
		BPTIlluminationSolver( const unsigned short _cameraPathSize = 3,
				const unsigned short _lightPathSize = 3 );
		~BPTIlluminationSolver();

		virtual void estimateRadiance( Ray _ray, const Scene& _scene, 
				std::vector< std::tuple<RGB, float> >& _samples );

	private:
		unsigned short cameraPathSize;
		unsigned short lightPathSize;
};

#endif
