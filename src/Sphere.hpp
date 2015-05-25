#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <iostream>

#include "glm.hpp"
#include "gtx/projection.hpp"
#include "gtc/random.hpp"

#include "aliases.hpp"
#include "Object.hpp"
#include "Scene.hpp"

class Sphere : public Object
{
public:
    Sphere();
    ~Sphere();

    virtual bool intersect( Ray _ray, RayHit& _hit );

    virtual glm::vec3 getNormalAt( glm::vec3 _p );

    virtual glm::vec3 getRandomSurfacePoint();

    virtual DiffGeoData getDiffGeoDataAtPoint( glm::vec3 _point ); 

    virtual DiffGeoData getSampledDiffGeoData();

    float radius;
};

#endif

