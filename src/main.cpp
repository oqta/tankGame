#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

GLfloat points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f
};

const int WINDOW_SIZE_X = 640;
const int WINDOW_SIZE_Y = 480;
const char* WINDOW_TITLE = "Tank Game";

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}

void glfwKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
}

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Can't load GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* pWindow = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "Window not created" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL()) {
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
	glfwSetKeyCallback(pWindow, glfwKeyCallBack);

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1, 1, 0, 1);
	{
		ResourceManager resourceManager(argv[0]);
		auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (!pDefaultShaderProgram)
		{
			std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
			return -1;
		}

		GLuint pointsVbo = 0;
		glGenBuffers(1, &pointsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colorsVbo = 0;
		glGenBuffers(1, &colorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		while (!glfwWindowShouldClose(pWindow))
		{

			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(pWindow);

			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}