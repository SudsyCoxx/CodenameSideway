#pragma once

#include <map>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utilities/Timer.hpp"
#include "../Window/WindowManager.hpp"

typedef unsigned int t_button;

using namespace Graphics;

class MouseHandler {
public:
    struct Position{
        double x,y;
    };
    
    static MouseHandler& GetInstance(){
        static MouseHandler instance;
        return instance;
    }
    
    static void PositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void ButtonCallback(GLFWwindow* window, int button, int action, int mods);
    
    void DisableCursor(){ glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    void HideCursor(){ glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
    void DefaultCursor(){ glfwSetInputMode(WindowManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
    
    Position GetPositon(){ return m_position; }
    double GetButtonHoldTime(t_button button);
private:
    bool PressMouseButton(t_button button);
    bool ReleaseMouseButton(t_button button);
    
    std::mutex m_lock;
	Utilities::Stopwatch m_time;
    Position m_position;
    std::map<t_button, double> m_ButtonStatus;
    
    MouseHandler(){
        m_time.Reset();
    }
protected:
};
