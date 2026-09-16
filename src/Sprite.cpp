#include "Sprite.hpp"

namespace cpuEng
{
    //Animated

    Sprite<ANIMATED>::Sprite(std::vector<Texture> t, std::string name, Dimensions hitbox, Position p)
    :
    m_texture(t),
    m_name(name),
    m_hitbox(hitbox),
    m_pos(p)

    {

    }

    Sprite<ANIMATED>::Sprite(std::vector<std::string> texture_paths, std::string name, Dimensions hitbox, Position p)
    :
    m_texture(texture_paths.size()),
    m_name(name),
    m_hitbox(hitbox),
    m_pos(p)
    {

    }





    //Static

    Sprite<STATIC>::Sprite(Texture t, std::string name, Dimensions hitbox, Position p)
    :
    m_texture(t),
    m_name(name),
    m_hitbox(hitbox),
    m_pos(p)

    {

    }

    Sprite<STATIC>::Sprite(std::string texture_path, std::string name, Dimensions hitbox, Position p) 
    : 
    m_texture(texture_path, p),
    m_name(name),
    m_hitbox(hitbox),
    m_pos(p)

    {

    }











}