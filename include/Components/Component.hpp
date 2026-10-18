#pragma once

#include <utility>
#include <unordered_map>
#include "Entity.hpp"
#include "Animation.hpp"



namespace cpuEng
{
    class Entity; //forward declaration to prevent problems with circular includes

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
        Position_Component(const Position& pos) : m_pos{pos} {} 
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

    class Texture_Component : public Component
    {
    public:
        Texture_Component(Texture& texture) : texture(texture) {}
        Texture& texture;
    };

    class Animation_Component : public Component
    {
    public:
        Animation_Component(Animation& animation) : animation(animation) {}
        Animation& animation;
    };

    class AnimationGroup_Component : public Component
    {
    public:
        AnimationGroup_Component(std::unordered_map<std::string, Animation*> animations = {}) : animations{animations}, currentAnimation{""} {}

        std::unordered_map<std::string, Animation*> animations;
        std::string currentAnimation;
        const Animation* getCurrentAnimation() const { return animations.at(currentAnimation); }
    };
};