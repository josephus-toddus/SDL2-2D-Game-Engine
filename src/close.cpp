#include <Window.hpp>
#include <stdexcept>

namespace cpuEng
{
    void close()
    {
        SDL_Quit();
    }
}