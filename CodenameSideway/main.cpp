
#include "Source\Window\WindowManager.hpp"

int main(int argc, char** argv) {

	// Create Window and Setup Window Properties
	Graphics::WindowManager::GetInstance().CreateWnd(640, 480, "Codename: Sideway");
	
	// Setup Graphics Stuff Here
	
	// Run Game
	Graphics::WindowManager::GetInstance().Run();

	return 0;
}
