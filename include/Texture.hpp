#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <cstdint>
#include <Position.hpp>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace cpuEng
{
    class Texture
    {
    public:
        
        Texture(std::string path, Position p);

        bool loaded();

        Position getPos();
    private:

        std::string m_path;
        Dimensions m_dim;
        Position m_pos;
        std::vector<std::uint32_t> m_texture;

        bool m_successfullyLoaded;

    };
}

#endif