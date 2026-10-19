#include "Window.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>


cpuEng::Window::Window(int width, int height) :
    m_width(width),
    m_height(height),
    m_totalPixels(width * height),
    m_pixels(m_totalPixels, 0x00000000),
    m_window(SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE)),
    m_surface(m_window ? SDL_GetWindowSurface(m_window) : nullptr),
    m_shouldClose(false)
    
{
    if (!m_window || m_surface == nullptr)
    {
        SDL_Log("Window or Surface could not be created! SDL_Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create SDL window or surface");
    }
    //make sure there is no blending, I wanna do it myself!!! :)
    SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_NONE);
}

cpuEng::Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

void cpuEng::Window::upDateWindow()
{
    m_surface = SDL_GetWindowSurface(m_window);

    if (!m_surface) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        return;
    }

    // Ensure framebuffer dimensions match the actual surface.
    if (m_width != m_surface->w || m_height != m_surface->h) {
        if (!Resize()) {
            return;
        }
    }

    if (SDL_MUSTLOCK(m_surface)) {
        if (SDL_LockSurface(m_surface) < 0) {
            SDL_Log("SDL_LockSurface failed: %s", SDL_GetError());
            return;
        }
    }

    auto* pixels = static_cast<std::uint8_t*>(m_surface->pixels);

    for (int y = 0; y < m_height; ++y) {
        auto* row = reinterpret_cast<std::uint32_t*>(
            pixels + y * m_surface->pitch
        );

        std::copy_n(
            m_pixels.data() + static_cast<std::size_t>(y) * m_width,
            m_width,
            row
        );
    }

    if (SDL_MUSTLOCK(m_surface)) {
        SDL_UnlockSurface(m_surface);
    }

    if (SDL_UpdateWindowSurface(m_window) < 0) {
        SDL_Log("SDL_UpdateWindowSurface failed: %s", SDL_GetError());
    }
}


void cpuEng::Window::setBackGround(const std::uint32_t& colour)
{
    for (std::uint32_t& i : m_pixels)
    {
        i = colour;
    }
}

bool cpuEng::Window::shouldClose()
{
    return m_shouldClose;
}



bool cpuEng::Window::Resize() 
{
    SDL_Surface* surface = SDL_GetWindowSurface(m_window);

    if (!surface) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        return false;
    }

    m_surface = surface;
    m_width = m_surface->w;
    m_height = m_surface->h;
    m_totalPixels = m_width * m_height;

    // Resize the CPU framebuffer to exactly match the window.
    m_pixels.assign(
        static_cast<std::size_t>(m_totalPixels),
        0xFF000000
    );

    return true;
}