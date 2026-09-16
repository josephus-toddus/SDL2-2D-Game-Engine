#include <Texture.hpp>

#ifndef SPRITE_HPP
#define SPRITE_HPP

#define STATIC false
#define ANIMATED true

namespace cpuEng
{
    template <bool animated>
    class Sprite;



    //The animated 
    template<>
    class Sprite<ANIMATED>
    {
    public:

        Sprite(std::vector<Texture> t, std::string name, Dimensions hitbox, Position p);
        Sprite(std::vector<std::string> texture_paths, std::string name, Dimensions hitbox, Position p);
    
    private:

        std::string m_name;
        std::vector<Texture> m_texture;
        Dimensions m_hitbox;
        Position m_pos;

    };


    
    //The static Sprite
    template<>
    class Sprite<STATIC>
    {
    public:

        Sprite(Texture t, std::string name, Dimensions hitbox, Position p);
        Sprite(std::string texture_path, std::string name, Dimensions hitbox, Position p);
    
    private:

        std::string m_name;
        Texture m_texture;
        Dimensions m_hitbox;
        Position m_pos;
    };
}

#endif