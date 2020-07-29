#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
	
	if(!gladLoadGL()){
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);
	
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1, 1, 0, 1);

    while (!glfwWindowShouldClose(pWindow))
    {
   
        glClear(GL_COLOR_BUFFER_BIT);
  
        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}