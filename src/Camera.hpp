#ifndef CAMERA_H_
#define CAMERA_H_

#include <vector>
#include <iostream>

#include "glm.hpp"
#include "Scene.hpp"
#include "aliases.hpp"
#include "Image.hpp"

//#include "gtx/type_precision.hpp"

class Camera
{
public:
    Camera(const unsigned int _res_width, const unsigned int _res_height);
    ~Camera();
    virtual void render( Scene& _scene );

    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;
    glm::i16vec2 resolution;
    glm::vec2 planeSize;
    float focalDistance;
    Image<RGB> image;

protected:
    void buildRays();
    std::vector< std::vector<Ray> > rays;


private:
    float aspect;
};

#endif

