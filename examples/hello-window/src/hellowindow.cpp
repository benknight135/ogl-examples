// Include standard headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

// Include OpenGL headers
#ifdef WITH_GLAD2
	#include <glad/gl.h>
#else
	#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(window == NULL){
        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
#ifdef WITH_GLAD2
	int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
#else
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	do{
		// Clear the screen.
		glClear( GL_COLOR_BUFFER_BIT );

		// Draw nothing
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
    exit(EXIT_SUCCESS);
}