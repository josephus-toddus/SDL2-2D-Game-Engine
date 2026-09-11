#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <memory>

#include "Position.hpp"

namespace cpuEng
{
    class Window
    {
    public:

        Window(const int& width, const int& height);
        ~Window();

        int checkEvent();

        void upDateWindow();

        void setBackGround(const std::uint32_t& colour);

    private:

        int m_height;
        int m_width;
        int m_totalPixels;

        std::vector<std::uint32_t> m_pixels;

        SDL_Window* m_window;
        SDL_Surface* m_surface;

        SDL_Event m_event;


    };
}
#endif