#pragma once
#include <utility>

namespace cpuEng
{
    class Component
    {
    public:
        virtual ~Component() = default;
    protected:
        Entity* p_owner;
    };

    class Position_Component : public Component
    {
    public:
        Position m_pos;
    };

    class Collision_Component : public Component
    {
    public:
        Dimensions m_dim;
    };

    class Velocity_Component : public Component
    {
    public:
        Vector2D m_speed;
        Vector2D m_acceleration;
    };

    class Horizontal_Gravity_Component : public Component
    {
    public:
        int x_gravityAcceleration;
    };

    class Vertical_Gravity_Component : public Component
    {
    public:
        int y_gravityAcceleration;
    };
};