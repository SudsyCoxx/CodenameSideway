#pragma once

#include <string>

#include "../Utilities/Singleton.hpp"
#include "../Utilities/SmartPointer.hpp"



#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphics {
	class WindowManager : public Utilities::Singleton<WindowManager> {
		friend class Utilities::Singleton<WindowManager>;
	public:
		~WindowManager();
	
		GLFWwindow* GetWindow() { return m_window; }
		void SetProperties();
		
		bool CreateWnd(int Width, int Height, std::string Title);
		void DestroyWnd();

		bool ShouldClose();

		static void WndSizeCallback(GLFWwindow* wnd, int width, int height);

	private:
		WindowManager(const WindowManager& s) = delete;
		WindowManager& operator=(const WindowManager& s) = delete;

		GLFWwindow* m_window;

		int m_width, m_height;
		unsigned int m_vao;

	protected:
		WindowManager();
	};
}