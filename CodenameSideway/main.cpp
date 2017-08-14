#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Source\Utilities\FPSManager.hpp"
#include "Source\Window\WindowManager.hpp"

int main(void)
{
	Utilities::FPSManager::GetInstance().Start();
	Graphics::WindowManager::GetInstance().CreateWnd(640, 480, "Codename: Sideway");

	while (!Graphics::WindowManager::GetInstance().ShouldClose())
	{
		Utilities::FPSManager::GetInstance().UpdateWindow();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(Graphics::WindowManager::GetInstance().GetWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}
