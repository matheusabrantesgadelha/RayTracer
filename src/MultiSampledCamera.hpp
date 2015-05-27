#ifndef PATHTRACECAMERA_H_
#define PATHTRACECAMERA_H_

#include "Camera.hpp"

#include "gtc/random.hpp"

/**
 * @brief The MultiSampledCamera class. Extends Camera class to provide Path Tracing.
 */
class MultiSampledCamera : public Camera
{
public:
    /**
     * @brief MultiSampledCamera constructor
     * @param _res_width Resolution width
     * @param _res_height Resolution height
     * @param _ns Number of sample paths per pixel
     */
    MultiSampledCamera(const unsigned int _res_width, const unsigned int _res_height, const unsigned int _ns);

    /**
     * @brief MultiSampledCamera destructor
     */
    ~MultiSampledCamera();

    /**
     * @brief render Method to render a scene using Path Tracing
     * @param _scene Scene representation
     */
    virtual void render( Scene& _scene);

private:
    /**
     * @brief numSamples Number of sample paths per pixel
     */
    unsigned int numSamples;
    /**
     * @brief bounces Number of bounces a path can have
     */
    unsigned int bounces;

    /**
     * @brief deltaDisplacement amount of displacement to apply to different rays from the same pixel
     */
    float deltaDisplacement;
};

#endif

