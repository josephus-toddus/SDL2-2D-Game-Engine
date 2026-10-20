#include "Texture.hpp"
#include <cstring>

cpuEng::Texture::Texture() :
    Texture({0x0, 0x00F800F8, 0x0, 0x00F800F8}, {2, 2})
{}

cpuEng::Texture::Texture(const std::string& path, bool should_load) : m_path(path), m_successfullyLoaded(false), m_dim{0, 0}
{
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

cpuEng::Texture::Texture(std::vector<std::uint32_t> texture, Dimensions dim) : m_successfullyLoaded(false), m_dim(dim), m_texture(texture)
{}

bool cpuEng::Texture::loaded() const
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

void cpuEng::Texture::load(const std::string& path)
{
    SDL_Surface* raw = IMG_Load(path.c_str());
    if (raw == nullptr)
    {
        //SDL_Log("Texture::load failed for '%s': %s", path.c_str(), IMG_GetError());
        return;
    }

    // Force a known layout: 4 bytes per pixel, ARGB. This makes the copy below safe.
    SDL_Surface* surface = SDL_ConvertSurfaceFormat(raw, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(raw);  



    if (surface == nullptr)
    {
        //SDL_Log("Convert failed for '%s': %s", path.c_str(), SDL_GetError());
        return;
    }

    m_dim.width  = surface->w;
    m_dim.height = surface->h;
    m_texture.assign(static_cast<std::size_t>(surface->w) * surface->h, 0x0);

    const auto* src = static_cast<const std::uint8_t*>(surface->pixels);
    for (int y = 0; y < surface->h; ++y)
    {
        std::memcpy(&m_texture[static_cast<std::size_t>(y) * surface->w],   // destination row
                    src + static_cast<std::size_t>(y) * surface->pitch,     // source row
                    static_cast<std::size_t>(surface->w) * sizeof(std::uint32_t)); // bytes per row
    }

    m_successfullyLoaded = true;
    SDL_FreeSurface(surface);
}

const std::vector<std::uint32_t>& cpuEng::Texture::getRawTexture() const
{   
    return m_texture;
}