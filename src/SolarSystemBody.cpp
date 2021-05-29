#include "SolarSystemBody.h"

SolarSystemBody::SolarSystemBody(float r, int sectorc, int stackc, vec3 dist, vec3 sc, float rotSp, uint texid)
    : Sphere(r, sectorc, stackc), textureId(texid), distance(dist), scale(sc), rotateSpeed(rotSp)
{
    matrix = mat4(1.0);
}

void SolarSystemBody::rotate(vec3 sunPos)
{
    matrix = mat4(1.0);

    vec3 orbitTranslate = vec3(distance.x, 0.0f, 0.0f) * sin(float(glfwGetTime()) * rotateSpeed * 0.3f)
            + vec3(0.0f, distance.y, 0.0f) * cos(float(glfwGetTime()) * rotateSpeed * 0.3f);
    matrix = glm::translate(matrix, orbitTranslate);
    matrix = glm::rotate(matrix, float(glfwGetTime() * 0.02f), vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, scale);
}

SolarSystemBody::~SolarSystemBody()
{

}

uint SolarSystemBody::getTextureId()
{
    return textureId;
}

mat4 SolarSystemBody::getMatrix()
{
    return matrix;
}
