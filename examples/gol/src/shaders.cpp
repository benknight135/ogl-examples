#include "shaders.h"

GLuint loadShaders(){
	// Create and compile our GLSL program from the shaders
    // Shader sources
    GLchar* vertexSource = R"glsl(
        #version 330 core

        // Input vertex data, different for all executions of this shader.
        layout(location = 0) in vec3 vertexPosition_modelspace;
		layout(location = 1) in vec4 vertexColor;

		// Output data will be interpolated for each fragment.
		out vec4 fragmentColor;

        // Values that stay constant for the whole mesh.
        uniform mat4 MVP;

        void main(){
            // Output position of the vertex, in clip space : MVP * position
	        gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

			// The color of each vertex will be interpolated
			// to produce the color of each fragment
			fragmentColor = vertexColor;
        }
    )glsl";
    GLchar* fragmentSource = R"glsl(
        #version 330 core

		// Interpolated values from the vertex shaders
		in vec4 fragmentColor;

        // Ouput data
        out vec4 color;

        void main()
        {
            // Output color = color specified in the vertex shader, 
			// interpolated between all 3 surrounding vertices
			color = fragmentColor;
        }
    )glsl";

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling OpenGL vertex shader..." << std::endl;
    glShaderSource(VertexShaderID, 1, &vertexSource , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	std::cout << "Compiling OpenGL fragment shader..." << std::endl;
    glShaderSource(FragmentShaderID, 1, &fragmentSource , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	std::cout << "Linking OpenGL shader program" << std::endl;
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        std::cerr << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}