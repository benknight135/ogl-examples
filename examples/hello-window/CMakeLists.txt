cmake_minimum_required(VERSION 3.9)

# Define executable name
set(APP_NAME "hello-window")

# Define source files
file (GLOB SRC_FILES
    "src/hellowindow.cpp"
)

# Build executable from source file
add_executable (${APP_NAME} ${SRC_FILES} ${GLAD_GL})
# Link libraries (glwf, glad)
target_link_libraries (${APP_NAME} glfw glad)

# Install app in 'bin' folder
install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})