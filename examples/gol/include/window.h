#pragma once

// Include standard headers
#include <cstdlib>
#include <iostream>

// Include OpenGL headers
#ifdef WITH_GLAD2
    // Glad v2 beta uses different header name
	#include <glad/gl.h>
#else
	#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

class Window{
public:
	Window(bool fullscreen = false, int width = 480, int height = 480);

	void clear();

	void update();

	bool isOpen();

	void centerWindow();

	GLFWwindow * getGLFWWindow();

	~Window();
private:
	GLFWmonitor* glfw_monitor;
	GLFWwindow * glfw_window;
};