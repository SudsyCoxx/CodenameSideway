#pragma once

#include <map>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utilities/Timer.hpp"
#include "../Utilities/Singleton.hpp"
#include "../Window/WindowManager.hpp"
#include "../MathFunctions/Vector.hpp"

typedef unsigned int t_button;

using namespace Graphics;

namespace Input {
	class MouseHandler : public Utilities::Singleton<MouseHandler> {
		friend class Utilities::Singleton<MouseHandler>;
	public:

		static void PositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void ButtonCallback(GLFWwindow* window, int button, int action, int mods);

		void DisableCursor() { glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
		void HideCursor() { glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
		void DefaultCursor() { glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

		MathFuncs::vec2 GetPositon() { return m_position; }
		double GetButtonHoldTime(t_button button);
	private:
		MouseHandler() {
			m_time.Reset();
		}
		MouseHandler(const MouseHandler& s) = delete;
		MouseHandler& operator=(const MouseHandler& s) = delete;

		bool PressMouseButton(t_button button);
		bool ReleaseMouseButton(t_button button);

		std::mutex m_lock;
		Utilities::Stopwatch m_time;
		MathFuncs::vec2 m_position;
		std::map<t_button, double> m_ButtonStatus;
	protected:
	};
}