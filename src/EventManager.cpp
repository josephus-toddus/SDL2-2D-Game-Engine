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
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    m_window.m_width = event.window.data1; // New width
                    m_window.m_height = event.window.data2; // New height
                    m_window.m_totalPixels = m_window.m_width * m_window.m_height; //New total pixels

                    m_window.m_surface = SDL_GetWindowSurface(m_window.m_window);

                    m_window.m_pixels = std::vector<std::uint32_t>(m_window.m_totalPixels, 0xFFFFFFFF);
                    return 1;
                }
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    m_window.m_shouldClose = true;
                    return -1;
                }
                break;
            
        }
    }
    return 0;
}