cmake_minimum_required(VERSION 3.9)

# Read version from file
file(READ "version.txt" ver)
message("version: ${ver}")

# Set project languages (CXX = C++)
# (May also add C# support in future)
set(PROJECT_LANGS CXX)

# Setup project
project(ogl-samples LANGUAGES ${PROJECT_LANGS} VERSION ${ver})

option(BUILD_TESTS "Build Unit tests" ON)
option(WITH_GLAD2 "Use glad v2 (beta)" ON)

# FetchContent used for external dependencies
# Will use a backport of FetchContent for cmake version < 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(${CMAKE_SOURCE_DIR}/cmake/backport/FetchContent.cmake)
else()
    include(FetchContent)
endif()

if (BUILD_TESTS) 
    # Get Catch2 from git repository for Unit Testing
    FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.6)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)

    include(CTest)
    include(Catch)
endif (BUILD_TESTS)

# Get GLFW from git repository
# GLFW is an Open Source, multi-platform library for 
# OpenGL, OpenGL ES and Vulkan development
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# Get GLAD from git repository
# Glad is an extension loader library used for access both OpenGL and OpenGL ES extensions 
# and modern versions of the core OpenGL or OpenGL ES APIs
if(WITH_GLAD2)
    # Use experimental Glad v2 beta

    # Set the definition so examples use correct version
    add_definitions(-DWITH_GLAD2)
    # CMakeLists.txt is not in the root of the repo
    # so requires setting the SOURCE_SUBDIR to the cmake folder
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG        glad2
            SOURCE_SUBDIR  cmake
    )
else()
    # Some examples have features not availble in v1 these will be disabled
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        glad
    )
endif()

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile") # core / compatibility
    if(WITH_GLAD2)
        set(GL_VERISON "" CACHE STRING "OpenGL version (empty means latest)")
        add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
        glad_add_library(glad REPRODUCIBLE API gl:${GLAD_PROFILE}=${GL_VERISON})
    else()
        set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.3,gles=\", no version means latest")
        set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
        add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
    endif()
endif()

# Get glm git repository
# Used for OpenGL mathematics
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

# Get linmath from git repository
# Used for linear mathematics
FetchContent_Declare(
        linmath
        GIT_REPOSITORY https://github.com/datenwolf/linmath.h.git
)

FetchContent_GetProperties(linmath)
if(NOT linmath_POPULATED)
    FetchContent_Populate(linmath)
    add_library(linmath INTERFACE)
    target_include_directories(linmath INTERFACE ${linmath_SOURCE_DIR})
endif()

# Get tinycthread from git repository
# Used for mutli-threaded
FetchContent_Declare(
        tinycthread
        GIT_REPOSITORY https://github.com/tinycthread/tinycthread.git
)

FetchContent_GetProperties(tinycthread)
if(NOT tinycthread_POPULATED)
    FetchContent_Populate(tinycthread)
    #add_library(tinycthread INTERFACE)
    #target_include_directories(tinycthread INTERFACE ${tinycthread_SOURCE_DIR})
    add_subdirectory(${tinycthread_SOURCE_DIR} ${tinycthread_BINARY_DIR})
endif()

# Add examples

# Hello World example
# Render an empty window with a title
add_subdirectory(examples/hello-window)

# Transparent window example
# Displays a triangle on a transparent window with UI decorations hidden
add_subdirectory(examples/alpha-window)

# PointCloud viewer example
# Load a PointCloud from file and view with interactive camera
add_subdirectory(examples/pointcloud)

# Game of Life example
# OpenGL implimentation of Conway's Game of Life
add_subdirectory(examples/gol)