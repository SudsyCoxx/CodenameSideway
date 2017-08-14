#pragma once

#include "../Utilities/Singleton.hpp"
#include "../Utilities/SmartPointer.hpp"
#include <GLFW/glfw3.h>

namespace Graphics {
	class WindowManager : Utilities::Singleton<WindowManager> {
	public:
		~WindowManager();
	
	private:
		WindowManager();
		WindowManager(const WindowManager& s) = delete;
		WindowManager& operator=(const WindowManager& s) = delete;

		Utilities::SmartPointer<GLFWwindow> m_Window;

	protected:
	};
}