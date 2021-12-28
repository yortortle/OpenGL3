#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "STDMacros.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void DidShaderCompile(unsigned int Shader);
void DidShaderProgramLink(unsigned int Shader);

unsigned int vertexShader;
unsigned int fragmentShader;

float texCoords[] =
{
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
};

float verticesTextureSample[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

float verticesColorData[] = 
{
	// positions         // colors
	 0.0f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	 0.9f,  -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.45f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

float verticesTwoTriangles[] =
{
    -1.f,  -0.5f, 0.0f,  //
	 0.f,  -0.5f, 0.0f,  //
	-0.5f,  0.5f, 0.0f,  //

	0.f, -0.5f, 0.0f,   //
	1.f, -0.5f, 0.0f,   //
	.5f,  0.5f, 0.0f,   //
};

float verticesRightTriangle[] =
{
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
};

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