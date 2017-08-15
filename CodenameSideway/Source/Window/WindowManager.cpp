#include "WindowManager.hpp"

#include "../Utilities/Logging.hpp"
#include "../Utilities/FPSManager.hpp"

#include "../Input/KeyHandler.hpp"
#include "../Input/MouseHandler.hpp"

#include "../Rendering/Objects/Square.hpp"

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
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void WindowManager::SetCallbacks() {
	glfwSetKeyCallback(GetWindow(), KeyHandler::Callback);
	glfwSetMouseButtonCallback(GetWindow(), MouseHandler::ButtonCallback);
	glfwSetCursorPosCallback(GetWindow(), MouseHandler::PositionCallback);
	glfwSetWindowSizeCallback(GetWindow(), WindowManager::WndSizeCallback);
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

	SetCallbacks();

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
	GetInstance().m_width = width;
	GetInstance().m_height = height;
}

void WindowManager::Run() {
	Utilities::FPSManager::GetInstance().Start();

	std::vector<Utilities::SmartPointer<Square>> r;
	r.push_back(new Square(vec3(0, 0, 0), vec2(1, 1)));
	r.push_back(new Square(vec3(-1, -1, 0), vec2(1, 1)));
	while (!ShouldClose()) {
		Utilities::FPSManager::GetInstance().UpdateFPS();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& object : r) {
			object->Setup();
			object->Draw();
		}

		glfwSwapBuffers(GetWindow());

		glfwPollEvents();

		if (KeyHandler::GetInstance().GetKeyHoldTime(GLFW_KEY_ESCAPE) > 0 || KeyHandler::GetInstance().GetKeyHoldTime(GLFW_KEY_Q) > 0) {
			glfwSetWindowShouldClose(GetWindow(), GLFW_TRUE);
		}
	}

	for (auto& object : m_renderableObjects) {
		object.second->Destroy();
	}

	DestroyWnd();
}

bool WindowManager::AddRenderableObject(std::string ObjectName , Utilities::SmartPointer<RenderInterface>& object) {
	if (m_renderableObjects.count(ObjectName) == 0) {
		m_renderableObjects[ObjectName] = object;
	}
	return false;
}