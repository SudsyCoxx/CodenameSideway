#include "MouseHandler.hpp"

using namespace Input;

void MouseHandler::PositionCallback(GLFWwindow* window, double xpos, double ypos){
    MouseHandler::GetInstance().m_position.x = xpos;
    MouseHandler::GetInstance().m_position.y = ypos;
}

void MouseHandler::ButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if(action == GLFW_PRESS){
        MouseHandler::GetInstance().PressMouseButton(button);
    }else if(action == GLFW_RELEASE){
        MouseHandler::GetInstance().ReleaseMouseButton(button);
    }
}

bool MouseHandler::PressMouseButton(t_button button){
    if(m_ButtonStatus.count(button) > 0) return false;

    std::lock_guard<std::mutex> lock(m_lock);
    m_ButtonStatus[button] = m_time.ElapsedMs();
    
    return true;
}

bool MouseHandler::ReleaseMouseButton(t_button button){
    if(m_ButtonStatus.count(button) == 0) return false;
    
    std::lock_guard<std::mutex> lock(m_lock);
    m_ButtonStatus.erase(button);
    
    return true;
}

double MouseHandler::GetButtonHoldTime(t_button button){
    return m_ButtonStatus.count(button) == 0 ? 0.0 : m_ButtonStatus[button];
}
