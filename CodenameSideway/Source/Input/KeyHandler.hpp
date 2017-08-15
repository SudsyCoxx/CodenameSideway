#pragma once

#include <map>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Utilities/Timer.hpp"

typedef unsigned int t_key;
typedef double t_keyPressedTime;

class KeyHandler {
public:
    static KeyHandler& GetInstance(){
        static KeyHandler instance;
        return instance;
    }
    
    static void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    double GetKeyHoldTime(t_key key);
private:
    std::mutex m_lock;
    
    std::map<t_key, t_keyPressedTime> m_KeyStatus;
    
    bool PressKey(t_key key);
    bool ReleaseKey(t_key key);
    
    Utilities::Stopwatch m_time;
    
    KeyHandler(){
		m_time.Reset();
    }
    
protected:
};
