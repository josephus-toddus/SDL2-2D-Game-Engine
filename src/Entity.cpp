#include "Entity.hpp"

namespace cpuEng
{
    Entity::Entity(const Position p, const Dimensions hitbox)
    {

    }

    bool Entity::checkCollisions(const Position& pos, const Dimensions& hitbox)
    {
        return m_pos.x > pos.x && m_pos.x < m_pos.x + hitbox.width &&
               m_pos.y > pos.y && m_pos.y < m_pos.y + hitbox.height
               ;
    }

    bool Entity::checkCollisions(const Entity& E)
    {
        return checkCollisions(E.m_pos, E.m_hitbox);
    }
}