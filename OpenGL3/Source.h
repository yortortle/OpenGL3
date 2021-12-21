#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "STDMacros.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void DidShaderCompile(unsigned int Shader);
void DidShaderProgramLink(unsigned int Shader);
void CreateShaderProgram();

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

//two triangles
float vertices[] =
{
    -1.f,  -0.5f, 0.0f,   //
	 0.f,  -0.5f, 0.0f,   //
	-0.5f,  0.5f, 0.0f,  //

	0.f, -0.5f, 0.0f,   //
	1.f, -0.5f, 0.0f,   //
	.5f,  0.5f, 0.0f,   //
};

//right side triangle
float vertices2[] =
{
	0.f, -0.5f, 0.0f,   //
	1.f, -0.5f, 0.0f,   //
	.5f,  0.5f, 0.0f,   //
};

int TerminateOpenGL(std::string msg) 
{
	LOG(msg); 
	glfwTerminate();
	return -1;
}
