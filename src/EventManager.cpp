#include "EventManager.hpp"

cpuEng::EventManager::EventManager(Window& window, InputManager& manager) :
m_manager(manager),
m_window(window)
{
    
}

int cpuEng::EventManager::CheckEvents()
{
    m_manager.Update();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_window.m_shouldClose = true;
                return -1;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    case SDL_WINDOWEVENT_RESIZED:
                        if (!m_window.Resize()) {
                            return -1;
                        }
                        break;

                    case SDL_WINDOWEVENT_EXPOSED:
                        // The main loop will redraw the window.
                        break;

                    case SDL_WINDOWEVENT_CLOSE:
                        m_window.m_shouldClose = true;
                        return -1;
                }
                break;
            
        }
    }
    return 0;
}