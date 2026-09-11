#include <cstdlib>
#include <SDL2/SDL.h>
#include <Window.hpp>
#include <stdexcept>

namespace cpuEng
{
    void init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            std::exit(1);
        }
    }
    std::unique_ptr<cpuEng::Window> initWindow(int w, int h)
    {
        std::unique_ptr<cpuEng::Window> window;
        try{
            window = std::make_unique<cpuEng::Window>(800, 600);
        }
        catch (const std::runtime_error& e) {
            SDL_Log("Exception: %s\n", e.what());
            SDL_Quit();
            std::exit(1);
        }
        return window;
    }
}