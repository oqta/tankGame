#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"

GLfloat points[] = {
	0.0f, 50.f, 0.0f,
	50.f, -50.f, 0.0f,
	-50.f, -50.f, 0.0f
};

GLfloat colors[] = {
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
	0.5f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f
};

glm::ivec2 windowSize(640, 480);
const char* WINDOW_TITLE = "Tank Game";

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height)
{
	windowSize.x = width;
	windowSize.y = height;
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

	GLFWwindow* pWindow = glfwCreateWindow(windowSize.x, windowSize.y, WINDOW_TITLE, nullptr, nullptr);
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

		auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
		if (!pSpriteShaderProgram)
		{
			std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map16x16.png");

		auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTexture", "SpriteShader", 50, 100);
		pSprite->setPosition(glm::vec2(300, 100));

		GLuint pointsVbo = 0;
		glGenBuffers(1, &pointsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colorsVbo = 0;
		glGenBuffers(1, &colorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	    GLuint texCoordVbo = 0;
		glGenBuffers(1, &texCoordVbo);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("tex", 0);

		glm::mat4 modelMatrix1 = glm::mat4(1.f);
		modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(100.f, 50.f, 0.f));

		glm::mat4 modelMatrix2 = glm::mat4(1.f);
		modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(590.f, 50.f, 0.f));

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f, static_cast<float>(windowSize.y), -100.f, 100.f);

		pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

		pSpriteShaderProgram->use();
		pSpriteShaderProgram->setInt("tex", 0);
		pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

		while (!glfwWindowShouldClose(pWindow))
		{

			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			tex->bind();

			pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix1);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix2);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			pSprite->render();
			glfwSwapBuffers(pWindow);

			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}