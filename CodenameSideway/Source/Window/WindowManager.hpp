#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>

#include "../Utilities/Singleton.hpp"
#include "../Utilities/SmartPointer.hpp"

#include "../Rendering/RenderInterface.hpp"

namespace Graphics {
	class WindowManager : public Utilities::Singleton<WindowManager> {
		friend class Utilities::Singleton<WindowManager>;
	public:
		~WindowManager();
	
		GLFWwindow* GetWindow() { return m_window; }
		void SetProperties();
		void SetCallbacks();
		
		bool CreateWnd(int Width, int Height, std::string Title);
		void Run();

		bool AddRenderableObject(std::string ObjectName, Utilities::SmartPointer<RenderInterface>& object);

		static void WndSizeCallback(GLFWwindow* wnd, int width, int height);

	private:
		WindowManager(const WindowManager& s) = delete;
		WindowManager& operator=(const WindowManager& s) = delete;
		
		void DestroyWnd();
		bool ShouldClose();

		GLFWwindow* m_window;

		int m_width, m_height;
		unsigned int m_vao;

		std::map<std::string, Utilities::SmartPointer<RenderInterface>> m_renderableObjects;

	protected:
		WindowManager();
	};
}