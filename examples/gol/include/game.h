#pragma once

// Include standard headers
#include <vector>
#include <iostream>

// Include OpenGL headers
#ifdef WITH_GLAD2
    // Glad v2 beta uses different header name
	#include <glad/gl.h>
#else
	#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

// OpenGL triangle
class GLTriangle{
public:
    // WARNING: Initalise after glfw and glad have been initalised
	GLTriangle(float size = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, 
               float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	void draw();

    void updatePosition(float x, float y, float z);
    void updateColor(float r, float g, float b, float a);

    // WARNING: cleanup before glfwTerminate (e.g. 'delete(golPixel);')
    ~GLTriangle();

private:
    GLuint colorArrayID;
    GLuint colorBuffer;
	GLuint vertexArrayID;
	GLuint vertexBuffer;
    float vertexData[18];
    float colorData[24];
    float unitSize;
};