#ifndef SPHERE_H
#define SPHERE_H

#include <glm.hpp>
#include "Vertex.h"
#include <math.h>
#include <vector>

using namespace glm;

class Sphere
{
private:
    float radius;
    int sectorCount;
    int stackCount;
    std::size_t count;
    std::vector<Vertex> SphereVertices;
    std::vector<int> indices;
    std::vector<int> lineIndices;
public:
    Sphere(float r, int sectorc, int stackc);
    ~Sphere();

    Vertex* getSphereVertices();
    std::size_t getNumOfVertices();
    std::vector<int> getIndices();
};

#endif // SPHERE_H
