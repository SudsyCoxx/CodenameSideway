#pragma once

#include <map>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utilities/Singleton.hpp"
#include "../Utilities/Timer.hpp"

typedef unsigned int t_key;
typedef double t_keyPressedTime;

namespace Input {
	class KeyHandler : public Utilities::Singleton<KeyHandler> {
		friend class Utilities::Singleton<KeyHandler>;
	public:
		static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		double GetKeyHoldTime(t_key key);

	private:
		KeyHandler() {
			m_time.Reset();
		}
		KeyHandler(const KeyHandler& s) = delete;
		KeyHandler& operator=(const KeyHandler& s) = delete;

		bool PressKey(t_key key);
		bool ReleaseKey(t_key key);

		Utilities::Stopwatch m_time;
		std::mutex m_lock;
		std::map<t_key, t_keyPressedTime> m_KeyStatus;
	protected:
	};
}
