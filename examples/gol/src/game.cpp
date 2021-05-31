#include "game.h"

// OpenGL triangle
// WARNING: Initalise after glfw and glad have been initalised
GLTriangle::GLTriangle(float size, float x, float y, float z, float r, float g, float b, float a):
	unitSize(size / 2), vertexData { 0.0f }, colorData { 0.0f } // initalise arrays with zero
	{
	// Create vertex array for square to represent GOL pixel entity
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenVertexArrays(1, &colorArrayID);
	glBindVertexArray(colorArrayID);

	// Create vertex buffer for triangle
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STREAM_DRAW);
	// Create color buffer for triangle
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STREAM_DRAW);

	updatePosition(x, y, z);
	if (a == 0.0f){ // set color to zero of alpha zero to fully hide object
		updateColor(0.0f, 0.0f, 0.0f, 0.0f);
	} else {
		updateColor(r, g, b, a);
	}
}

void GLTriangle::draw(){
	// Load vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Load color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	
	// Draw triangle
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2 triangles with 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void GLTriangle::updatePosition(float x, float y, float z){
	/*
	square
	-1.0f,-1.0f, 0.0f, // triangle 1 : begin
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f, // triangle 1 : end
    1.0f, -1.0f, 0.0f, // triangle 2 : begin
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, // triangle 2 : end
	*/
	/*
	triangle
	-1.0f, -1.0f, 0.0f,
  	1.0f, -1.0f, 0.0f,
   	0.0f,  1.0f, 0.0f,
	*/
	/*
	cube
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
	*/
	for(int i = 0; i < 18; i += 3){
		if (i == 0){
			vertexData[i] = -unitSize + x;
			vertexData[i + 1] = -unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		} else if (i == 1*3){
			vertexData[i] = -unitSize + x;
			vertexData[i + 1] = unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		} else if (i == 2*3){
			vertexData[i] = unitSize + x;
			vertexData[i + 1] = -unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		} else if (i == 3*3){
			vertexData[i] = unitSize + x;
			vertexData[i + 1] = -unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		} else if (i == 4*3){
			vertexData[i] = unitSize + x;
			vertexData[i + 1] = unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		} else if (i == 5*3){
			vertexData[i] = -unitSize + x;
			vertexData[i + 1] = unitSize + y;
			vertexData[i + 2] = 0.0f + z;
		}
	}

	// Update buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLTriangle::updateColor(float r, float g, float b, float a){
	for(int i = 0; i < 24; i += 4)
	{
		colorData[i] = r;
		colorData[i + 1] = g;
		colorData[i + 2] = b;
		colorData[i + 3] = a;
	}

	// Update buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colorData), colorData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// WARNING: cleanup before glfwTerminate (e.g. 'delete(golPixel);')
GLTriangle::~GLTriangle(){
	// Cleanup
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteVertexArrays(1, &colorArrayID);
}