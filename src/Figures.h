#ifndef FIGURES_H
#define FIGURES_H

#include <glm.hpp>
#include "Vertex.h"

using namespace glm;

// данные о вершинах
int triangleVertexCount = 3;
int cubeVertexCount = 3 * 2 * 6;
//Vertex triangleVertexes[] = {
//    //                ВЕРШИНА                   ЦВЕТ
//    Vertex(vec3( 0.0f,  1.0f,  0.0f),   vec3(0.5f, 0.8f, 0.5f)),
//    Vertex(vec3(-1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f)),
//    Vertex(vec3( 1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f))
//};

Vertex cubeVertexes[] = {
    //               Вершина                      Нормаль                    Цвет                   Текстура
    //Back
    Vertex(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 0.5f,  0.8f,  0.5f), vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 0.9f,  0.1f,  0.9f), vec2(-0.5f,  0.5f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 0.3f, 0.15f,  0.9f), vec2(-0.5f, -0.5f)),

    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 0.3f, 0.15f,  0.9f), vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 1.0f,  1.0f,  1.0f), vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec3( 0.5f,  0.8f,  0.5f), vec2( 0.5f,  0.5f)),

    //Up
    Vertex(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3( 0.5f,  0.8f,  0.5f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3( 0.9f,  0.1f,  0.9f), vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3( 0.6f,  0.6f,  0.9f), vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3( 0.5f,  0.8f,  0.5f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3( 0.6f,  0.6f,  0.9f), vec2(-0.5f,  0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec3(0.25f,  0.9f,  0.9f), vec2( 0.5f,  0.5f)),

    //Down
    Vertex(vec3( 0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 1.0f,  1.0f,  1.0f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 0.3f, 0.15f,  0.9f), vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 0.1f,  0.0f,  0.7f), vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 1.0f,  1.0f,  1.0f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 0.1f,  0.0f,  0.7f), vec2(-0.5f,  0.5f)),
    Vertex(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec3( 0.6f,  0.1f,  0.1f), vec2( 0.5f,  0.5f)),

    //Left
    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.3f, 0.15f,  0.9f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.9f,  0.1f,  0.9f), vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.6f,  0.6f,  0.9f), vec2(-0.5f,  0.5f)),

    Vertex(vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.3f, 0.15f,  0.9f), vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.6f,  0.6f,  0.9f), vec2(-0.5f,  0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec3( 0.1f,  0.0f,  0.7f), vec2( 0.5f,  0.5f)),

    //Right
    Vertex(vec3( 0.5f, -0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3( 1.0f,  1.0f,  1.0f), vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3( 0.5f,  0.8f,  0.5f), vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3(0.25f,  0.9f,  0.9f), vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f, -0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3( 1.0f,  1.0f,  1.0f), vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3(0.25f,  0.9f,  0.9f), vec2(-0.5f,  0.5f)),
    Vertex(vec3( 0.5f, -0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec3( 0.6f,  0.1f,  0.1f), vec2( 0.5f,  0.5f)),

    //Front
    Vertex(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3(0.25f,  0.9f,  0.9f), vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3( 0.6f,  0.6f,  0.9f), vec2(-0.5f,  0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3( 0.1f,  0.0f,  0.7f), vec2(-0.5f, -0.5f)),

    Vertex(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3( 0.1f,  0.0f,  0.7f), vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3( 0.6f,  0.1f,  0.1f), vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec3(0.25f,  0.9f,  0.9f), vec2( 0.5f,  0.5f))
};

#endif
