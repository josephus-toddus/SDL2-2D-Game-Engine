#include "../include/Window.hpp"

#include <stdexcept>
#include <algorithm>

namespace cpuEng
{
    Window::Window(const int& width, const int& height) :
        m_width(width),
        m_height(height),
        m_totalPixels(width * height),
        m_pixels(m_totalPixels, 0x00000000),
        m_window(SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE)),
        m_surface(m_window ? SDL_GetWindowSurface(m_window) : nullptr)
        
    {
        if (!m_window || m_surface == nullptr)
        {
            SDL_Log("Window or Surface could not be created! SDL_Error: %s\n", SDL_GetError());
            throw std::runtime_error("Failed to create SDL window or surface");
        }
        SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_NONE);
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_window);
    }

    int Window::checkEvent()
    {
        int result = 0;
        while (SDL_PollEvent(&m_event))
        {
            if (m_event.type == SDL_QUIT)
            {
                return 1;
            }
            else if (m_event.type == SDL_WINDOWEVENT)
            {
                if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    m_width = m_event.window.data1; // New width
                    m_height = m_event.window.data2; // New height
                    m_totalPixels = m_width * m_height; //New total pixels

                    m_surface = SDL_GetWindowSurface(m_window);

                    m_pixels = std::vector<std::uint32_t>(m_totalPixels, 0x00000000);
                    return 2;
                }
                else if (m_event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    return 1;
                }
            }
        }
        return result;
    }

    void Window::upDateWindow()
    {
        if (SDL_MUSTLOCK(m_surface))
        {
            SDL_LockSurface(m_surface);
        }

        if (m_pixels.size() < m_surface->h * m_surface->pitch) 
        {
            m_pixels.reserve(m_surface->h * m_surface->pitch);
        }
        std::uint8_t* pixels = static_cast<std::uint8_t*>(m_surface->pixels);

        for (int i = 0; i < m_surface->h; ++i)
        {
            std::uint32_t* row = reinterpret_cast<std::uint32_t*>(pixels + i * m_surface->pitch);
            for (int j = 0; j < m_surface->w; ++j)
            {
                row[j] = m_pixels[i * m_width + j];
            }
        }

        if (SDL_MUSTLOCK(m_surface))
        {
            SDL_UnlockSurface(m_surface);
        }

        SDL_UpdateWindowSurface(m_window);
    }
    void Window::setBackGround(const std::uint32_t& colour)
    {
        for (std::uint32_t& i : m_pixels)
        {
            i = colour;
        }
    }
}