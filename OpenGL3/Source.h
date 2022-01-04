#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "STDMacros.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void DidShaderCompile(unsigned int Shader);
void DidShaderProgramLink(unsigned int Shader);

unsigned int vertexShader;
unsigned int fragmentShader;

float CubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
};

glm::vec3 cubePositions[] =
{
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] =
{
   0, 1, 3, // first triangle
   1, 2, 3  // second triangle
};

float ColorPlaneVertices[] =
{
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
};

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