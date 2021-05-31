#pragma once

// Include standard headers
#include <cstdlib>
#include <iostream>
#include <chrono>

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
	Window(bool fullscreen = false, int width = 480, int height = 480, bool borderless = true);

	void clear();

	void update();

	bool isOpen();

	float getAspectRatio();

	int getWidth();

	int getHeight();

	float getFPS();

	void centerWindow();

	GLFWwindow * getGLFWWindow();

	~Window();
private:
	GLFWmonitor* glfw_monitor;
	GLFWwindow * glfw_window;
	float fps;
	std::chrono::steady_clock::time_point last_update_time;
};