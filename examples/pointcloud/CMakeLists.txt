cmake_minimum_required(VERSION 3.9)

# Define executable name
set(APP_NAME "pointcloud")

include_directories(include)

# Define source files
file (GLOB SRC_FILES
    "src/*.cpp"
)

# Build executable from source file
add_executable (${APP_NAME} ${SRC_FILES} ${GLAD_GL})
# Link libraries (glwf, glad)
target_link_libraries (${APP_NAME} glfw glad glm)

# Install app in 'bin' folder
install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})