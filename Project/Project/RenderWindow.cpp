#include <GL\glew.h>
#include "RenderWindow.hpp"
#define WIN32_LEAN_AND_MEAN
#undef APIENTRY
#include <Windows.h>
#include <iostream>

renderWindow::renderWindow(GLFWwindow* window)
{
	this->window = window;
	threadRunning = false;
}

renderWindow::~renderWindow()
{

}

void renderWindow::createThread()
{
	threadPointer = new std::thread(&renderWindow::renderThread, this);
	if (threadPointer)
	{
		threadRunning = true;
	}
}

bool renderWindow::isThreadRunning() const
{
	return threadRunning;
}

void renderWindow::update()
{
	mainScene.updateScene();

	glfwSetWindowTitle(window, fpsCount.get().c_str());

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		mainScene.getCamera().ry += (float)(xpos - oldx) / 50.0f;
		mainScene.getCamera().rx += (float)(ypos - oldy) / 50.0f;
		mainScene.getCamera().genRot();
		oldx = xpos;
		oldy = ypos;
	}
	else
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		oldx = xpos;
		oldy = ypos;
	}

	glm::vec3 up = mainScene.getCamera().rot * glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 forward = mainScene.getCamera().rot * glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 strafe = glm::cross(up, forward);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mainScene.getCamera().translation = glm::translate(mainScene.getCamera().translation, forward*glm::vec3(0.1f, 0, -0.1));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mainScene.getCamera().translation = glm::translate(mainScene.getCamera().translation, forward*glm::vec3(-0.1f, 0, 0.1));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mainScene.getCamera().translation = glm::translate(mainScene.getCamera().translation, strafe*glm::vec3(0.1f, 0, -0.1f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mainScene.getCamera().translation = glm::translate(mainScene.getCamera().translation, strafe*glm::vec3(-0.1f, 0, 0.1));
	}
}

void renderWindow::renderThread()
{
	glfwMakeContextCurrent(window);
	// enable vsync
	glfwSwapInterval(1);

	// not sure why I need to make my object here

	mainScene.requestBuffer();

	while (!glfwWindowShouldClose(window))
	{
		render();
		fpsCount.tick();
	}
	threadRunning = false;
}


// render function
// would be possible to have multiple scenes to toggle between
void renderWindow::render()
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	mainScene.getCamera().height = (float)height;
	mainScene.getCamera().width = (float)width;
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	mainScene.renderScene();

	glfwSwapBuffers(window);
}