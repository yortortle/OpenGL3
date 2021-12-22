#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "STDMacros.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void DidShaderCompile(unsigned int Shader);
void DidShaderProgramLink(unsigned int Shader);
unsigned int CreateShaderProgram(const char* vertSource, const char* fragSource);

unsigned int vertexShader;
unsigned int fragmentShader;
//unsigned int shaderProgram;

float verticesColorData[] = 
{
	// positions         // colors
	 0.0f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	 0.9f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.45f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

//two triangles
float verticesTwoTriangles[] =
{
    -1.f,  -0.5f, 0.0f,  //
	 0.f,  -0.5f, 0.0f,  //
	-0.5f,  0.5f, 0.0f,  //

	0.f, -0.5f, 0.0f,   //
	1.f, -0.5f, 0.0f,   //
	.5f,  0.5f, 0.0f,   //
};

//right side triangle
float verticesRightTriangle[] =
{
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};

//left side
float verticesLeftTriangle[] =
{
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
};

int TerminateOpenGL(std::string msg) 
{
	LOG(msg); 
	glfwTerminate();
	return -1;
}


const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"  //attribute position 0
"layout (location = 1) in vec3 aColor;\n" //attribute position 1
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
//"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"   ourColor = aColor;\n "
"}\0";

const char* LeftTriangleFragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
//d"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
//"   FragColor = vertexColor;\n"
"	FragColor = vec4(0.5f, 0.5f, 0.8f, 1.0f);\n"
"}\n";

const char* RightTriangleFragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
//"	FragColor = ourColor;\n"
//"	FragColor = vec4(0.0f, 0.2f, 1.f, 1.0f);\n"
"}\n";