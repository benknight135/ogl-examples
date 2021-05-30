#pragma once

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
	GLTriangle(int x, int y, int z);

	void draw();

    void updatePosition(int x, int y, int z);

    // WARNING: cleanup before glfwTerminate (e.g. 'delete(golPixel);')
    ~GLTriangle();

private:
    GLuint colorArrayID;
    GLuint colorBuffer;
	GLuint vertexArrayID;
	GLuint vertexBuffer;
};

// Game Of Life pixel entity
// Will store the status of the entity (position, alive/dead)
// and handle drawing the object in the window
class GolEntity{
public:
    // WARNING: Initalise after glfw and glad have been initalised
	GolEntity(bool alive, int x, int y, int z);

    void updateState(GolEntity golEntityNeighbours[8]);

    // Draw OpenGL shape reprsentation of entity in window
	void draw();

    void updatePosition(int x, int y, int z);
    
    // Get alive/dead state of entity
    bool isAlive();

    // WARNING: Cleanup before glfwTerminate (e.g. 'delete(golPixel);')
    ~GolEntity();

private:
	GLTriangle* gl_shape;
    bool alive;
};