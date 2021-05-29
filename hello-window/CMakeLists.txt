cmake_minimum_required(VERSION 3.9)

# Define executable name
set(APP_NAME "hello-window")

# Define source files
file (GLOB SRC_FILES
    "src/*.cpp"
)

# Build executable from soruce files
add_executable (${APP_NAME} ${SRC_FILES})
# Link libraries (glwf, glad)
target_link_libraries (${APP_NAME} glfw glad)

# Install app in 'bin' folder
install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})