#ifndef CAMERA_H
#define CAMERA_H

#include "Helpers.h"
#include <math.h>
#include <string>
#include <GL/glew.h>        // для поддержки расширений, шейдеров и так далее
#include <GLFW/glfw3.h>     // Непосредственно сам GLFW
#include <glm.hpp>          // библиотека графической математики
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class Camera
{
private:
    static Camera* instance;

    vec3 position;
    vec3 front;
    vec3 up;
    float speed;
    float yaw;
    float pitch;

    Camera();
    Camera(const Camera&);
    Camera& operator=(Camera&);
public:
    static Camera* getInstance();
    static void deleteInstance();

    void move(string side);
    void rotate(vec2 pos);

    mat4 getView();
};

#endif // CAMERA_H
