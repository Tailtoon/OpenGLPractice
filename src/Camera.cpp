#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
{
    position = vec3(0.0f, 0.0f, 1.0f);
    front = vec3(0.0f, 0.0f, -1.0f);
    up = vec3(0.0f, 1.0f, 0.0f);
    speed = 0.002f;
    yaw = -90.0f;
    pitch = 0.0f;
}

Camera* Camera::getInstance()
{
    if (instance == nullptr)
        instance = new Camera;
    return instance;
}

void Camera::deleteInstance()
{
    if (instance != nullptr)
        delete instance;
}

void Camera::move(string side)
{
    if (side == "left")
    {
        position -= normalize(cross(front, up)) * speed;
    }
    else if (side == "right")
    {
        position += normalize(cross(front, up)) * speed;
    }
    else if (side == "front")
    {
        position += front * speed;
    }
    else if (side == "back")
    {
        position -= front * speed;
    }
}

void Camera::rotate(vec2 pos)
{
    yaw += pos.x * 0.1f;
    pitch += pos.y * 0.1f;

    if(pitch > 89.0f)
      pitch =  89.0f;
    if(pitch < -89.0f)
      pitch = -89.0f;

    vec3 direction;
    direction.x = cos(radians(yaw)) * cos(radians(pitch));
    direction.y = sin(radians(pitch));
    direction.z = sin(radians(yaw)) * cos(radians(pitch));
    front = normalize(direction);
}

mat4 Camera::getView()
{
    mat4 view = lookAt(position, position + front, up);
    return view;
}
