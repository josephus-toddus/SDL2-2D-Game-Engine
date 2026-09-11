#include <cstdlib>
#include <SDL2/SDL.h>
#include <Window.hpp>
#include <stdexcept>

namespace cpuEng
{
    bool init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return true;
        }
        return false;
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
            return nullptr;
        }
        return window;
    }
}