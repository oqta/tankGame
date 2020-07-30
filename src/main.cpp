#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderProgram.h"

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


const char* vertexShader =
"#version 450\n"
"layout(location = 0) in vec3 vertexPosition;"
"layout(location = 1) in vec3 vertexColor;"
"out vec3 color;"
"void main() {"
"   color = vertexColor;"
"   gl_Position = vec4(vertexPosition, 1.0);"
"}";


const char* fragmentShader =
"#version 450\n"
"in vec3 color;"
"out vec4 fragmentColor;"
"void main() {"
"   fragmentColor = vec4(color, 1.0);"
"}";

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

int main(void)
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

	std::string sVertexShader(vertexShader);
	std::string sFragmentShader(fragmentShader);
	Renderer::ShaderProgram shaderProgram(sVertexShader, sFragmentShader);
	if (!shaderProgram.isCompiled()) 
	{
		std::cerr << "Can't create shader program!" << std::endl;
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

		shaderProgram.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(pWindow);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}