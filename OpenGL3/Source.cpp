#include "Source.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (!window) return TerminateOpenGL("Failed to create GLFW window\n");
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return TerminateOpenGL("Failed to init GLAD\n");

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader lShader = Shader("UniformVertex.vs", "UniformFragment.fs");
	Shader rShader = Shader("BaseVertex.vs", "BaseFragment.fs");

	//two triangles
	//{
		//// declares VBOS and VAOS
		//unsigned int VBOs[2], VAOs[2];
		//glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
		//glGenBuffers(2, VBOs);

		//// first (left) triangle setup
		//glBindVertexArray(VAOs[0]);
		//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLeftTriangle), verticesLeftTriangle, GL_STATIC_DRAW);
		////position attribute
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		//glEnableVertexAttribArray(0);

		//// second (right) triangle setup
		//glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
		//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
		//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColorData), verticesColorData, GL_STATIC_DRAW);
		////position attribute
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		//glEnableVertexAttribArray(0);
		////color attribute
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	// vertex attribute 1 (color data)
		//glEnableVertexAttribArray(1);
		//// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
		//// glBindBuffer(GL_ARRAY_BUFFER, 0); //no need to unbind
	//}

	//set up vertex data and buffers and configure the vertex attributes
	float vertices[] = 
	{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = 
	{
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//load and create a texture
	unsigned int texture;
	glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effectd on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//{
		//	//left triangle shaders
		//	float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
		//	lShader.use();
		//	lShader.setVec4("FrameColor", greenValue);
		//	//lShader.setFloat("xOffset", 0.5f);
		//	glBindVertexArray(VAOs[0]);
		//	glDrawArrays(GL_TRIANGLES, 0, 3);

		//	//right triangle
		//	rShader.use();
		//	glBindVertexArray(VAOs[1]);
		//	glDrawArrays(GL_TRIANGLES, 0, 3);
		//}

		{
			// bind Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			// render container
			rShader.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		//check and call events and swapping buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0; 
}

void DidShaderCompile(unsigned int Shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}
}

void DidShaderProgramLink(unsigned int ShaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
		LOG("ERROR::SHADERPROGRAM::LINK_FAILED\n", infoLog);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

