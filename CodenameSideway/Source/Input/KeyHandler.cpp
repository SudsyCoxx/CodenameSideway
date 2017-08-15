
#include "KeyHandler.hpp"
#include "../Utilities/Logging.hpp"
#include <sstream>

using namespace Utilities;

void KeyHandler::Callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        KeyHandler::GetInstance().PressKey(key);
    }else if(action == GLFW_RELEASE){
        KeyHandler::GetInstance().ReleaseKey(key);
    }
}

double KeyHandler::GetKeyHoldTime(t_key key){
    return m_KeyStatus.count(key) == 0 ? 0 : m_time.ElapsedMs() - m_KeyStatus[key];
}

bool KeyHandler::PressKey(t_key key){
    if(m_KeyStatus.count(key) > 0){
        std::stringstream ss;
        ss << key;
        Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Key already pressed", ss.str());
        
        return false;
    }
    
    std::stringstream ss;
    ss << char(key);
	Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Key pressed", ss.str());
    
    std::lock_guard<std::mutex> lock(m_lock);
    m_KeyStatus[key] = m_time.ElapsedMs();
        
    return true;
}

bool KeyHandler::ReleaseKey(t_key key){
    if(m_KeyStatus.count(key) == 0){
        std::stringstream ss;
        ss << key;
		Utilities::Logging::GetInstance().Log(ID_DEBUG, -1, "Key already pressed", ss.str());
        return false;
    }
    
    std::lock_guard<std::mutex> lock(m_lock);
    m_KeyStatus.erase(key);
    
    return true;
}
