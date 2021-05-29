#include "Shaders.h"
#include "Helpers.h"
#include <stdio.h>
#include <stdlib.h>

using namespace glm;

GLuint createShaderFromSources(const char* vertexShader, const char* fragmentShader){
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    CHECK_GL_ERRORS();

    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    CHECK_GL_ERRORS();

    GLuint shaderProgram = glCreateProgram ();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    CHECK_GL_ERRORS();

    /*int infologLength = 0;
    glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0){
        GLchar* infoLog = (GLchar*)malloc(static_cast<size_t>(infologLength));
        if (infoLog == nullptr){
            printf("ERROR: Could not allocate InfoLog buffer");
            exit(1);
        }
        int charsWritten = 0;
        glGetShaderInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
        printf("Shader InfoLog:\n%s", infoLog );
        free(infoLog);
    }
    CHECK_GL_ERRORS();*/
    
    return shaderProgram;
}

GLuint createShader(){
    // Шейдер вершин
    const char* vertexShader = STRINGIFY_SHADER(
        // vertex attribute
        attribute vec3 aPos;
        attribute vec3 aColor;
        attribute vec3 aNormal;
        attribute vec2 aCoord;
        // uniforms
        uniform mat4 uModelViewProjMat;
        uniform mat4 uViewMat;
        uniform mat4 uProjMat;
        // output
        varying vec3 vColor;
        varying vec3 vNormal;
        varying vec2 vCoord;
        varying vec3 vFragPos;
        varying vec3 vLightPos;
        void main () {
            vec4 vertexVec4 = vec4(aPos, 1.0f);      // последняя компонента 1, тк это точка
            // вычисляем позицию точки в пространстве OpenGL
            gl_Position = uModelViewProjMat * vertexVec4;

            vNormal = mat3(uModelViewProjMat) * aNormal;

            vFragPos = vec3(uModelViewProjMat * vec4(aPos, 1.0f));

            vLightPos = vec3(uProjMat * uViewMat * vec4(0.0f, 0.0f, 0.0f, 1.0f));

            // цвет и текстурные координаты просто пробрасываем для интерполяции
            vColor = aColor;
            vCoord = aCoord;
        }
    );
    const char* fragmentShader = STRINGIFY_SHADER(
        varying vec3 vColor;
        varying vec3 vNormal;
        varying vec2 vCoord;
        varying vec3 vFragPos;
        varying vec3 vLightPos;
        uniform sampler2D newTexture0;

        void main () {
            // ambient
            vec3 ambient = 0.1f * vec3(texture2D(newTexture0, vCoord));

            // diffuse
            vec3 norm = normalize(vNormal);
            vec3 lightDir = normalize(vLightPos - vFragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = vec3(0.9f, 0.9f, 0.9f) * diff * vec3(texture2D(newTexture0, vCoord));

            vec3 result = ambient + diffuse;
            gl_FragColor = vec4(result * vColor, 1.0);

            //gl_FragColor = texture2D(newTexture0, vCoord) * vec4(vColor * ambient, 1.0);

        }
    );

    GLuint shader = createShaderFromSources(vertexShader, fragmentShader);
    CHECK_GL_ERRORS();
    return shader;
}

GLuint createShaderForSun()
{
    // Шейдер вершин
    const char* vertexShader = STRINGIFY_SHADER(
        // vertex attribute
        attribute vec3 aPos;
        attribute vec3 aColor;
        attribute vec3 aNormal;
        attribute vec2 aCoord;
        // uniforms
        uniform mat4 uModelViewProjMat;
        uniform mat4 uViewMat;
        uniform mat4 uProjMat;
        // output
        varying vec3 vColor;
        varying vec3 vNormal;
        varying vec2 vCoord;
        varying vec3 vFragPos;
        void main () {
            vec4 vertexVec4 = vec4(aPos, 1.0f);      // последняя компонента 1, тк это точка
            // вычисляем позицию точки в пространстве OpenGL
            gl_Position = uModelViewProjMat * vertexVec4;

            vNormal = mat3(uModelViewProjMat) * aNormal;

            vFragPos = vec3(uModelViewProjMat * vec4(aPos, 1.0));

            // цвет и текстурные координаты просто пробрасываем для интерполяции
            vColor = aColor;
            vCoord = aCoord;
        }
    );
    const char* fragmentShader = STRINGIFY_SHADER(
        varying vec3 vColor;
        varying vec3 vNormal;
        varying vec2 vCoord;
        varying vec3 vFragPos;
        uniform sampler2D newTexture0;

        void main () {
                    gl_FragColor = texture2D(newTexture0, vCoord) * vec4(vColor * 1.5f, 1.0f);

        }
    );

    GLuint shader = createShaderFromSources(vertexShader, fragmentShader);
    CHECK_GL_ERRORS();
    return shader;
}
