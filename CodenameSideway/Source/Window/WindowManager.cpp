#include "WindowManager.hpp"

#include "../Utilities/Logging.hpp"
#include "../Utilities/FPSManager.hpp"

using namespace Graphics;
using namespace Utilities;

WindowManager::WindowManager() {

}

WindowManager::~WindowManager() {

}

void WindowManager::SetProperties() {
	// TODO: Make a property sheet of a class that maintains the properties for the window/game
	Utilities::Logging::GetInstance().Log(ID_TRACE, 0, "Setting Window Properies", "");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool WindowManager::CreateWnd(int Width, int Height, std::string Title) {
	Utilities::Logging::GetInstance().Log(ID_TRACE, 0, "Creating Window", "");

	m_width = Width;
	m_height = Height;

	if (!glfwInit()) {
		Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Failed to init GLFW", "");
		return false;
	}

	SetProperties();

	m_window = glfwCreateWindow(m_width, m_height, Title.c_str(), NULL, NULL);
	if (!m_window)
	{
		Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Failed to create Window", "");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Failed to init glew", "");
		glfwTerminate();
		return false;
	}

	glfwSwapInterval(0);

	glGenVertexArrays(1 ,&m_vao);
	glBindVertexArray(m_vao);

	return true;
}

void WindowManager::DestroyWnd() {
	Utilities::Logging::GetInstance().Log(ID_TRACE, 0, "Destroying Window", "");
	glfwTerminate();
}

bool WindowManager::ShouldClose() {
	return glfwWindowShouldClose(m_window);
}

void WindowManager::WndSizeCallback(GLFWwindow* wnd, int width, int height) {

}

void WindowManager::Run() {
	Utilities::FPSManager::GetInstance().Start();

	while (!ShouldClose()) {
		Utilities::FPSManager::GetInstance().UpdateFPS();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		glfwSwapBuffers(GetWindow());

		glfwPollEvents();
	}

	DestroyWnd();
}