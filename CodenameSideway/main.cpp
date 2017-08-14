#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Source\Utilities\FPSManager.hpp"
#include "Source\Window\WindowManager.hpp"

#include <iostream>

#include "Source\MathFunctions\MathFuncs.hpp"

int main(void)
{
	Utilities::FPSManager::GetInstance().Start();
	Graphics::WindowManager::GetInstance().CreateWnd(640, 480, "Codename: Sideway");

	while (!Graphics::WindowManager::GetInstance().ShouldClose())
	{
		Utilities::FPSManager::GetInstance().UpdateFPS();
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		/* Swap front and back buffers */
		glfwSwapBuffers(Graphics::WindowManager::GetInstance().GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}
