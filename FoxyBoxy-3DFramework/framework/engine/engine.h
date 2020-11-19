#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <engine/settings.h>
#include <object/object.h>
#include <textureLoader/textureLoader.h>
#include <shader/shader.h>
#include <camera/camera.h>

GLFWwindow* window;

// engine prototypes
int engineInit(void);
void engineStop(void);
int engineCloseWindow(void);
float engineGetDT(void);
void engineUpdateDT(void);
void engineUpdateInput(void);
void engineSwapBuffers(void);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
extern void processInput(GLFWwindow* window);

int engineInit(void)
{
	std::cout << "=================\n";
	std::cout << "Initialising GLFW\n";
	std::cout << "=================\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow((int)SCR_WIDTH, (int)SCR_HEIGHT, windowName, NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "ERROR: unable to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: unable to initialise GLAD" << std::endl;
		return -1;
	}

	glfwSwapInterval(1);

	std::cout << "==============\n";
	std::cout << "GLFW is ready!\n";
	std::cout << "==============\n";
	return 0;
}

void engineStop(void)
{
	
}

int engineCloseWindow(void)
{
	return glfwWindowShouldClose(window);
}

float engineGetDT(void)
{
	return deltaTime;
}

void engineUpdateDT(void)
{
	double currentTime = glfwGetTime();
	deltaTime = currentTime - oldTime;
	oldTime = currentTime;
}

void engineUpdateInput(void)
{
	processInput(window);
}

void engineSwapBuffers(void)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCR_WIDTH = (float)width;
	SCR_HEIGHT = (float)height;
}


#endif
