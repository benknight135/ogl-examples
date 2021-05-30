#include "camera.h"
#include "shaders.h"

Camera::Camera(int x, int y, int z, float fov){
    // Compile and load shaders
    programID = loadShaders();

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45 degree Field of View, 1:1 ratio, display range : 0.1 unit <-> 100 units
    Projection = glm::perspective(glm::radians(fov), 1.0f / 1.0f, 0.1f, 100.0f);
    // Camera matrix
    View = glm::lookAt(
        glm::vec3(x,y,z), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

void Camera::update(){
    // Use our shader
    glUseProgram(this->programID);

    // Send our transformation to the currently bound shader, 
    // in the "MVP" uniform
    glUniformMatrix4fv(this->MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

GLuint Camera::getProgramID(){
    return this->programID;
}

Camera::~Camera(){
    glDeleteProgram(programID);
}