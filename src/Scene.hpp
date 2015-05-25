#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <memory>
#include <algorithm>

#include "glm.hpp"
#include "gtc/random.hpp"
#include "gtc/constants.hpp"

#include "aliases.hpp"
#include "Object.hpp"

class Object;

class Scene : public std::enable_shared_from_this<Scene>
{
public:
    Scene();
    ~Scene();
    std::shared_ptr<Scene> getptr();
    void addObject( std::shared_ptr<Object> _obj );
    bool intersect( Ray _ray, RayHit& _hit);
    RGB pathCast(Ray _ray);
    RGB bidirectionalPathCast( Ray _ray );

    std::vector< std::shared_ptr<Object> > objects;
    std::vector< std::shared_ptr<Object> > lights;
    RGB environmentColor;

    void setLightBounces( int _numBounces );
    void setLightPathSize( const unsigned int _lightPathSize);
    void setCameraPathSize( const unsigned int _cameraPathSize);

private:
    void computeLightPath(Ray _orgRay, std::vector<RayHit>& _path , unsigned int _bounces);
    void computeCameraPath(Ray _orgRay, std::vector<RayHit>& _path , unsigned int _bounces);

    unsigned int lightBounces;
    unsigned int lightPathSize;
    unsigned int cameraPathSize;

};

#endif

