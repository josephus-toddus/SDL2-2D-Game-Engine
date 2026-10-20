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
    Texture();
    
    Texture(const std::string& path, bool should_load);

    bool loaded() const;

    void load();

    void unload();

    

private:

    Texture(std::vector<std::uint32_t> texture, Dimensions dim); // for making the fallback texture in TextureManager
    const std::vector<std::uint32_t>& getRawTexture() const; // only for Renderer

    void load(const std::string& path);

    std::string m_path;
    Dimensions m_dim;
    std::vector<std::uint32_t> m_texture;

    bool m_successfullyLoaded;

    friend class TextureManager;
    friend class Renderer;
    friend class Animation;

};

}
