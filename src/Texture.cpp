#include "Texture.hpp"


cpuEng::Texture::Texture(std::string path, bool should_load) : m_path(path), m_successfullyLoaded(true)
{
    //This inits loading pngs the first time a Texture is created
    static bool first = true;
    if (first)
    {
        first = false;
        IMG_Init(IMG_INIT_PNG);
    }

    //load the image into ram
    if (should_load)
    {
        load(path);
    }
    else
    {
        m_texture = std::vector<std::uint32_t>();
    }
}

cpuEng::Texture::Texture(std::vector<std::uint32_t> texture, Dimensions dim) : m_successfullyLoaded(true), m_dim(dim), m_texture(texture)
{}

bool cpuEng::Texture::loaded()
{
    return m_successfullyLoaded; //is a bool
}

void cpuEng::Texture::unload()
{
    m_texture.clear();            // clears the vector freeing up ram
    m_successfullyLoaded = false; //sets the bool to false
}

void cpuEng::Texture::load()
{
    load(m_path);
}

void cpuEng::Texture::load(std::string path)
{
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

    SDL_FreeSurface(temp_surface);
}
