// TODO: надо ли?
// #define GLFW_INCLUDE_GLCOREARB 1 // Tell GLFW to include the OpenGL core profile header
#define GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GLEXT
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>        // для поддержки расширений, шейдеров и так далее
#include <GLFW/glfw3.h>     // Непосредственно сам GLFW
#include <glm.hpp>          // библиотека графической математики
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "PngLoader.h"
#include "Helpers.h"
#include "Vertex.h"
#include "Sphere.h"
#include "Figures.h"
#include "SolarSystemBody.h"
#include "Shaders.h"
#include "ObjLoader.h"
#include "Camera.h"

// Документация
// https://www.opengl.org/sdk/docs/man/html/

using namespace std;
using namespace glm;

#define MATH_PI 3.14159265

// Текущие переменные для модели
bool leftButtonPressed = false;
bool rightPressed = false;
bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;
int width = 1024;
int height = 1024;
double lastCursorPosX = 512.0;
double lastCursorPosY = 512.0;

void glfwErrorCallback(int error, const char* description) {
    printf("OpenGL error = %d\n description = %s\n\n", error, description);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Выходим по нажатию Escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
            aPressed = true;
        else aPressed = false;
    } else if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
            dPressed = true;
        else dPressed = false;
    } else if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
            wPressed = true;
        else wPressed = false;
    } else if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
            sPressed = true;
        else sPressed = false;
    }
}

void glfwMouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
    // обработка левой кнопки
    if(button == GLFW_MOUSE_BUTTON_1){
        if(state == GLFW_PRESS){
            leftButtonPressed = true;
        }else{
            leftButtonPressed = false;
        }
    }
    // обработка правой кнопки
    if(button == GLFW_MOUSE_BUTTON_2){
        if(state == GLFW_PRESS){
            rightPressed = true;
        }else{
            rightPressed = false;
        }
    }
}

void glfwCursorCallback(GLFWwindow* window, double x, double y) {
    Camera* camera = Camera::getInstance();
    // при нажатой левой кнопки - вращаем по X и Y
    if(leftButtonPressed)
    {
        double centerx = width / 2;
        double centery = height / 2;

        double offsetx = x - lastCursorPosX;
        double offsety = lastCursorPosY - y;

        camera->rotate(vec2(offsetx, offsety));
    }

    // при нажатой левой кнопки - перемещаем по X Y
    if(rightPressed)
    {

    }

    lastCursorPosX = x;
    lastCursorPosY = y;
}

void glfwScrollCallback(GLFWwindow* window, double scrollByX, double scrollByY) {
}

int main(int argc, char *argv[]) {

    // окно
    GLFWwindow* window = 0;

    // обработчик ошибок
    glfwSetErrorCallback(glfwErrorCallback);

    // инициализация GLFW
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }

    // создание окна
#ifdef __APPLE__
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#endif
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(1024, 1024, "Simple example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);        // вертикальная синхронизация
    CHECK_GL_ERRORS();

    // Обработка клавиш и прочего
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(window, glfwCursorCallback);
    glfwSetScrollCallback(window, glfwScrollCallback);

    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();
    
    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();

    // Инициализация отладки
    if(glDebugMessageCallback){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Коллбек ошибок OpenGL
        glDebugMessageCallback((GLDEBUGPROC)glDebugOut, 0);

        // Более высокий уровень отладки
        // GLuint unusedIds = 0;
        // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
    }
    CHECK_GL_ERRORS();
    
    const unsigned char* version = glGetString(GL_VERSION);
    printf("OpenGL version = %s\n", version);

    // оотношение сторон
    int width = 0;
    int height = 0;
    // Размер буффера кадра
    glfwGetFramebufferSize(window, &width, &height);
    CHECK_GL_ERRORS();
    
    // задаем отображение
    glViewport(0, 0, width, height);
    CHECK_GL_ERRORS();

    // Шейдеры
    GLuint shaderProgram = createShader();
    GLuint shaderProgramForSun = createShaderForSun();
    CHECK_GL_ERRORS();

    // аттрибуты вершин шейдера
    int posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    int normalAttribLocation = glGetAttribLocation(shaderProgram, "aNormal");
    int colorAttribLocation = glGetAttribLocation(shaderProgram, "aColor");
    int texAttribLocation = glGetAttribLocation(shaderProgram, "aCoord");

    CHECK_GL_ERRORS();

    // юниформы шейдера
    int modelViewProjMatrixLocation = glGetUniformLocation(shaderProgram, "uModelViewProjMat");
    int modelViewLocation = glGetUniformLocation(shaderProgram, "uViewMat");
    CHECK_GL_ERRORS();

    Sphere sphere(1.0f, 100, 100);

    // VBO, данные о вершинах
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, triangleVertexCount * sizeof(Vertex), triangleVertexes, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, cubeVertexCount * sizeof(Vertex), cubeVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sphere.getNumOfVertices() * sizeof(Vertex), sphere.getSphereVertices(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS();
    
    // отключаем отображение задней части полигонов
    //glEnable(GL_CULL_FACE);
    // отбрасываться будут задние грани
    //glCullFace(GL_BACK);
    // Определяем, в каком направлении должный обходиться вершины, для передней части (против часовой стрелки?)
    // задняя часть будет отбрасываться
    glFrontFace(GL_CCW);
    CHECK_GL_ERRORS();

    // проверка глубины
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    CHECK_GL_ERRORS();

    // текущее время
    double time = glfwGetTime();

    // Создаем объекты солнечной системы
    vector<SolarSystemBody> SolarSystem;
    for (int i = 0; i < 9; i++)
    {
        // Загрузка текстуры объекта
        ImageData info = loadPngImage(("/home/tailtoon/OpenGL/OpenGL_Practice_FULL-template/res/test" + to_string(i) + ".png").c_str());
        uint textureId = 0;
        if(info.loaded){
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,              // формат внутри OpenGL
                         info.width, info.height, 0,            // ширинна, высота, границы
                         info.withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, info.data); // формат входных данных
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            CHECK_GL_ERRORS();
        }

        // матрица модель-вид-проекция
        vec3 distance;
        vec3 sc;
        float rotateSpeed;
        float constant = 696340 * 4;
        switch (i)
        {
        case 0: //Солнце
            distance = vec3(0.0f, 0.0f, 0.0f);
            sc = vec3(1.0f) * (696340/constant);
            rotateSpeed = 0;
            break;
        case 1: //Меркурий
            distance = vec3(0.2f, 0.2f, 0.0f);
            sc = vec3(1.0f) * (2440/constant);
            rotateSpeed = 0.48;
            break;
        case 2: //Венера
            distance = vec3(0.3f, 0.3f, 0.0f);
            sc = vec3(1.0f) * (6052/constant);
            rotateSpeed = 0.35;
            break;
        case 3: //Земля
            distance = vec3(0.4f, 0.4f, 0.0f);
            sc = vec3(1.0f) * (6378/constant);
            rotateSpeed = 0.30;
            break;
        case 4: //Марс
            distance = vec3(0.5f, 0.5f, 0.0f);
            sc = vec3(1.0f) * (3397/constant);
            rotateSpeed = 0.24;
            break;
        case 5: //Юпитер
            distance = vec3(0.6f, 0.6f, 0.0f);
            sc = vec3(1.0f) * (71490/constant);
            rotateSpeed = 0.13;
            break;
        case 6: //Сатурн
            distance = vec3(0.7f, 0.7f, 0.0f);
            sc = vec3(1.0f) * (60270/constant);
            rotateSpeed = 0.10;
            break;
        case 7: //Уран
            distance = vec3(0.8f, 0.8f, 0.0f);
            sc = vec3(1.0f) * (25560/constant);
            rotateSpeed = 0.07;
            break;
        case 8: //Нептун
            distance = vec3(0.9f, 0.9f, 0.0f);
            sc = vec3(1.0f) * (24760/constant);
            rotateSpeed = 0.05;
            break;
        }
        //modelViewProjMatrix = rotate(modelViewProjMatrix, M_PI_2f32, vec3(1.0f, 0.0f, 0.0f));
        //modelViewProjMatrix = rotate(modelViewProjMatrix, float(time), vec3(0.0f, 0.0f, 1.0f));

        SolarSystem.push_back(SolarSystemBody(1.0f, 100, 100, distance, sc, rotateSpeed, textureId));
    }

    Camera* camera = Camera::getInstance();

    while (!glfwWindowShouldClose(window)){
        // приращение времени
        double newTime = glfwGetTime();
        //double timeDelta = newTime - time;
        time = newTime;

        // wipe the drawing surface clear
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (aPressed)
        {
            camera->move("left");
        }
        if (dPressed)
        {
            camera->move("right");
        }
        if (wPressed)
        {
            camera->move("front");
        }
        if (sPressed)
        {
            camera->move("back");
        }

        for (int i = 0; i < 9; i++)
        {
            if (i == 0)
                glUseProgram (shaderProgramForSun);
            else glUseProgram(shaderProgram);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, SolarSystem[i].getTextureId());

            // выставляем матрицу трансформации в пространство OpenGL
            SolarSystem[i].rotate(vec3(0, 0, 0));
            mat4 proj = perspective(radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
            glUniformMatrix4fv(modelViewProjMatrixLocation, 1, false, glm::value_ptr(proj * camera->getView() * SolarSystem[i].getMatrix()));
            mat4 view = camera->getView();
            glUniformMatrix4fv(modelViewLocation, 1, false, glm::value_ptr(view));

            // sizeof(Vertex) - размер блока данных о вершине
            // OFFSETOF(Vertex, color) - смещение от начала
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Позиции
            glEnableVertexAttribArray(posAttribLocation);
            glVertexAttribPointer(posAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, pos));
            // Normals
            glEnableVertexAttribArray(normalAttribLocation);
            glVertexAttribPointer(normalAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, normal));
            // Цвет вершин
            glEnableVertexAttribArray(colorAttribLocation);
            glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, color));
            // Textures
            glEnableVertexAttribArray(texAttribLocation);
            glVertexAttribPointer(texAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, texCoord));
            CHECK_GL_ERRORS();

            // рисуем
            //glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount); // draw points 0-35 from the currently bound VAO with current in-use shader
            //glDrawArrays(GL_TRIANGLES, 0, sphere.getNumOfVertices());
            glDrawElements(GL_TRIANGLES,                    // primitive type
                           SolarSystem[i].getIndices().size(),         // # of indices
                           GL_UNSIGNED_INT,                 // data type
                           SolarSystem[i].getIndices().data());        // offset to indices

            // VBO off
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Camera::deleteInstance();

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
