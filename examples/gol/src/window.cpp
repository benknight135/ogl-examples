#include "window.h"

Window::Window(bool fullscreen, int width, int height, bool borderless): fps(0) {
    // Initalise glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
    // Enable transparent frame buffer
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	// Remove window decoration (title bar, boarder, etc...)
    if (borderless)
	    glfwWindowHint(GLFW_DECORATED, false);

    this->glfw_monitor = glfwGetPrimaryMonitor();
    // Check monitor is valid
    if (!this->glfw_monitor){
        std::cerr << "Invalid GLFW monitor in Window" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create window
    if (fullscreen){
        const GLFWvidmode* mode = glfwGetVideoMode(this->glfw_monitor);
        this->glfw_window = glfwCreateWindow(mode->width, mode->height, "Game of Life", NULL, NULL);
    } else {
        this->glfw_window = glfwCreateWindow(width, height, "Game of Life", NULL, NULL);
    }
    // Check window is valid
    if(this->glfw_window == NULL){
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(this->glfw_window);

    // Initalise glad
    // Must be called after window creation
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
	glfwSetInputMode(this->glfw_window, GLFW_STICKY_KEYS, GL_TRUE);

    centerWindow();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
}

void Window::clear(){
    // Clean screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(){
    // Swap buffers
    glfwSwapBuffers(this->glfw_window);
    glfwPollEvents();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update_time).count();
    fps = 1.0f/(ms/1000.0f);
    last_update_time = now;
}

bool Window::isOpen(){
    // Check if escape key is pressed or window was closed
    return glfwGetKey(this->glfw_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(this->glfw_window) == 0;
}

GLFWwindow * Window::getGLFWWindow(){
    return this->glfw_window;
}

int Window::getWidth(){
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->glfw_window, &windowWidth, &windowHeight);
    return windowWidth;
}

int Window::getHeight(){
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->glfw_window, &windowWidth, &windowHeight);
    return windowHeight;
}

float Window::getAspectRatio(){
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->glfw_window, &windowWidth, &windowHeight);
    float ratio = (float)windowWidth / (float)windowHeight;
    return ratio;
}

float Window::getFPS(){
    return this->fps;
}

// Center window on monitor
void Window::centerWindow()
{
    // Get monitor
    const GLFWvidmode *mode = glfwGetVideoMode(this->glfw_monitor);
    if (!mode)
        return;

    // Get monitor position
    int monitorX, monitorY;
    glfwGetMonitorPos(this->glfw_monitor, &monitorX, &monitorY);

    // Get window size
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->glfw_window, &windowWidth, &windowHeight);

    // Move window to monitor center
    glfwSetWindowPos(this->glfw_window,
                     monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);
}

Window::~Window(){
    glfwTerminate();
}