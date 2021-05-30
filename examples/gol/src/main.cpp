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

// Include GOL headers
#include "window.h"
#include "camera.h"
#include "game.h"

int main(void)
{  
	// Create window 
	// also initalises OpenGL so must be at start of program
    Window* window = new Window(true);

	// Create camera
    Camera* camera = new Camera(0, 0, 5);

    // Setup Game of Life entities
    // Must be initalised after Window as entities require OpenGL to be ready
	GolEntity* golEntity = new GolEntity(true, 2, 0, 0);

	int i = 0;

	do{
		// Clear window for new frame
		window->clear();

		// Update camera perpective
        camera->update();
		
        // Draw GOL pixels
		//golEntity->updatePosition(i, 0, 0);
		golEntity->draw();

		// Update window frame
		window->update();
		// i++;
		// if (i > 200)
		// 	i = 0;
		//std::cout << i << std::endl;
	} // Check if the ESC key was pressed or the window was closed
	while(window->isOpen());

    // Cleanup
	// (required to clean OpenGL objects in correct order)
    delete(golEntity);
	delete(camera);
	// Calls 'glfwTerminate' so all OpenGL object should be cleaned
	// before removing the window
	delete(window);

    exit(EXIT_SUCCESS);
}