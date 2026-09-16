#include "Texture.hpp"

namespace cpuEng
{
    Texture::Texture(std::string path, Position p) : m_path(path), m_successfullyLoaded(true), m_pos(p)
    {
        static bool first = true;
        if (first)
        {
            first = false;
            IMG_Init(IMG_INIT_PNG);
        }

        SDL_Surface* temp_surface = IMG_Load(path.c_str());
        if (temp_surface == nullptr)
        {
            m_successfullyLoaded = false;
        }

        m_dim.height = temp_surface->h;
        m_dim.width = temp_surface->h;

        m_texture = std::vector<std::uint32_t>(m_dim.area(), 0x0);

        std::uint32_t* pixels = static_cast<std::uint32_t*>(temp_surface->pixels);
        for (int i = 0; i < temp_surface->h; ++i)
        {
            for (int j = 0; j < temp_surface->w; ++j)
            {
                m_texture[i * (temp_surface->w) + j] = pixels[i * (temp_surface->pitch / 4) + j];
            }
        }

    }

    bool Texture::loaded()
    {
        return m_successfullyLoaded;
    }

    Position Texture::getPos()
    {
        return m_pos;
    }
};