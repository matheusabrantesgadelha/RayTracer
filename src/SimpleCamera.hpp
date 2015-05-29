#ifndef SIMPLECAMERA_H_ 
#define SIMPLECAMERA_H_ 

#include "Camera.hpp"

class SimpleCamera : public Camera
{
public:
	SimpleCamera( const unsigned int _res_width, const unsigned int _res_height,
			const std::shared_ptr<IlluminationSolver> _solver );

	virtual void render( Scene& _scene );
};

#endif
