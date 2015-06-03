#ifndef OBJECT_H_
#define OBJECT_H_

#include "aliases.hpp"
#include "Material.hpp"
#include "Scene.hpp"
#include "DiffGeomData.hpp"

class Scene;
struct DiffGeoData;

class Object : public std::enable_shared_from_this<Object>
{
public:
    Object();

    std::shared_ptr<Object> getptr();
    virtual bool intersect( Ray _ray, RayHit& _hit ) = 0;
    virtual glm::vec3 getNormalAt( glm::vec3 _p ) = 0;
    virtual glm::vec3 getRandomSurfacePoint( float& _pdf ) = 0;
    virtual DiffGeoData getDiffGeoDataAtPoint( glm::vec3 _point ) = 0;
    virtual DiffGeoData getSampledDiffGeoData( float& _pdf ) = 0;
	virtual float getArea() = 0;
    bool isLight();

    unsigned int id;
    std::shared_ptr<Scene> scene;
    glm::vec3 center;
    std::shared_ptr<Material> material;

};

#endif

