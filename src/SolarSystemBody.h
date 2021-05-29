#ifndef SOLARSYSTEMBODY_H
#define SOLARSYSTEMBODY_H

#include "Sphere.h"
#include "Helpers.h"
#include <math.h>
#include <GL/glew.h>        // для поддержки расширений, шейдеров и так далее
#include <GLFW/glfw3.h>     // Непосредственно сам GLFW
#include <glm.hpp>          // библиотека графической математики
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

class SolarSystemBody: public Sphere
{
private:
    //texture
    uint textureId;
    mat4 matrix;
    vec3 distance;
    vec3 scale;
    float rotateSpeed;
public:
    SolarSystemBody(float r, int sectorc, int stackc, vec3 dist, vec3 sc, float rotSp, uint texid);
    ~SolarSystemBody();

    void rotate(vec3 sunPos);

    uint getTextureId();
    mat4 getMatrix();
};

#endif // SOLARSYSTEMBODY_H
