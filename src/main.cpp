#include "../include/Window.hpp"
#include <stdexcept>

int main(int argc, char** argv) 
{
    
    std::unique_ptr<cpuEng::Window> window;
    
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