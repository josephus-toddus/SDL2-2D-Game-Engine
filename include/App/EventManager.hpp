#pragma once

#include <SDL2/SDL.h>
#include "InputManager.hpp"
#include "Window.hpp"
#include <unordered_map>

namespace cpuEng
{

class EventManager
{

public:
    EventManager(Window& window, InputManager& manager);

    int CheckEvents(); // returns whether the game should quit or not

    KeyCode Transalate(SDL_Scancode scan);

private:

    InputManager& m_manager;
    Window& m_window;

    //std::unordered_map <KeyCode, SDL_Scancode> m_KeyToScan; //I might not need this, let's see
};

}