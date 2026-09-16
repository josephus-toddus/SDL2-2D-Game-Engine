#include "../include/Window.hpp"
#include <stdexcept>
#include "init.cpp"
#include "close.cpp"
#include "colours.hpp"

int main(int argc, char** argv) 
{
    
    std::unique_ptr<cpuEng::Window> window;
    window = cpuEng::initWindow(800, 600);
    if (window == nullptr)
    {
        return -1;
    }

    while(!window->shouldClose()) 
    {

        window->setBackGround(WHITE);
        window->upDateWindow();
        
        SDL_Delay(16); // Delay to limit frame rate

    }
    
    cpuEng::close();
    return 0;
}