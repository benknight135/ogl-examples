#include "game.h"

// OpenGL triangle
// WARNING: Initalise after glfw and glad have been initalised
GLTriangle::GLTriangle(int x, int y, int z){
	// Create vertex array for square to represent GOL pixel entity
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenVertexArrays(1, &colorArrayID);
	glBindVertexArray(colorArrayID);

	// Create triangle data for vertex buffer
	const static GLfloat g_vertex_buffer_data[] { 
		-1.0f + x, -1.0f + y, 0.0f + z,
		1.0f + x, -1.0f + y, 0.0f + z,
		0.0f + x,  1.0f + y, 0.0f + z,
	};

	// One color for each vertex.
	static const GLfloat g_color_buffer_data[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};

	// Create vertex buffer for triangle
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// Create color buffer for triangle
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void GLTriangle::updatePosition(int x, int y, int z){
	// Create triangle data for vertex buffer
	const static GLfloat g_vertex_buffer_data[] { 
		-1.0f + x, -1.0f + y, 0.0f + z,
		1.0f + x, -1.0f + y, 0.0f + z,
		0.0f + x,  1.0f + y, 0.0f + z,
	};

	// Create vertex buffer for triangle
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

// WARNING: cleanup before glfwTerminate (e.g. 'delete(golPixel);')
GLTriangle::~GLTriangle(){
	// Cleanup
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteVertexArrays(1, &colorArrayID);
}

// Game Of Life pixel entity
// Will store the status of the entity (position, alive/dead)
// and handle drawing the object in the window
// WARNING: Initalise after glfw and glad have been initalised
GolEntity::GolEntity(bool alive, int x_pos, int y_pos, int z_pos) :
	alive(alive)
{
	//set inital position of shape representing entity
	gl_shape = new GLTriangle(x_pos, y_pos, z_pos);
};

void GolEntity::updateState(GolEntity golEntityNeighbours[8]){
	//TODO check alive/dead state based on neighbour entities
	// Rules:
	// 1. Any live cell with two or three live neighbours survives.
	// 2. Any dead cell with three live neighbours becomes a live cell.
	// 3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.
}

// Draw OpenGL shape reprsentation of entity in window
void GolEntity::draw(){
	this->gl_shape->draw();
}

void GolEntity::updatePosition(int x, int y, int z){
	this->gl_shape->updatePosition(x, y, z);
}

// Get alive/dead state of entity
bool GolEntity::isAlive(){
	return this->alive;
}

// WARNING: Cleanup before glfwTerminate (e.g. 'delete(golPixel);')
GolEntity::~GolEntity(){}