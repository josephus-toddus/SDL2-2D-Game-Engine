#include "../include/Window.hpp"
#include <stdexcept>
#include <cstdio>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    std::unique_ptr<cpuEng::Window> window;
    try{
        window = std::make_unique<cpuEng::Window>(800, 600);
    } catch (const std::runtime_error& e) {
        SDL_Log("Exception: %s\n", e.what());
        SDL_Quit();
        return -1;
    }
    window->setBackGround(0xFF00FFFF); //RGB
    while(true) {
        window->setBackGround(0xFF00FFFF);
        window->upDateWindow();
        
        SDL_Delay(16); // Delay to limit frame rate

        if (window->checkEvent() == 1)
        {
            break;
        }
    }
    
    SDL_Quit();
    return 0;
}