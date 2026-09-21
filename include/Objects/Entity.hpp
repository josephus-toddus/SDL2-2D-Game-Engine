#include <Texture.hpp>

#pragma once

namespace cpuEng
{
    class Entity
    {
    public:

        Entity(const Position p, const Dimensions hitbox);

        bool checkCollisions(const Position& pos, const Dimensions& hitbox);
        bool checkCollisions(const Entity& E);

    protected:

        Dimensions m_hitbox;
        Position m_pos;

    };
};