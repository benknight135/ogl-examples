#pragma once

// Include OpenGL headers
#ifdef WITH_GLAD2
    // Glad v2 beta uses different header name
	#include <glad/gl.h>
#else
	#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
    Camera(int x = 0, int y = 0, int z = 3, float fov = 45.0f);

    void update();

    GLuint getProgramID(); 

    ~Camera();

private:
    GLuint programID;
    GLuint MatrixID;
    glm::mat4 MVP;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
};