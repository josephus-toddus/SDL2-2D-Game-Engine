#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <cstdint>
#include <Position.hpp>

#pragma once

namespace cpuEng
{
    class Texture
    {
    public:
        
        Texture(std::string path, Position p, bool should_load);

        bool loaded();

        void load();

        void unload();

        Position getPos();
    private:

        std::string m_path;
        Dimensions m_dim;
        Position m_pos;
        std::vector<std::uint32_t> m_texture;

        bool m_successfullyLoaded;

        void load(std::string path);

    };
};
