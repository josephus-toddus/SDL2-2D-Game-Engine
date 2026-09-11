#include <SDL2/SDL.h>
#include <string>
#include <Position.hpp>

namespace cpuEng
{
    class Texture
    {
    public:
        
        Texture(std::string path);
    private:

        std::string m_path;
        Dimensions m_dim;

    };
}