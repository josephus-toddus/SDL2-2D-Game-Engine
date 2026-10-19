#pragma once

#include "Entity.hpp"
#include "Animation.hpp"
#include "ComponentRegistery.hpp"
#include "SceneManager.hpp"

#include <utility>
#include <unordered_map>


namespace cpuEng
{


class Position_Component : public Component
{
public:
    Position_Component(const Position& pos) : pos{pos} {} 
    Position pos;
}; //Done

class Collision_Component : public Component
{
public:
    Collision_Component(const Dimensions& dim) : dim(dim) {}
    Dimensions dim;
};//Done

class Velocity_Component : public Component
{
public:
    Velocity_Component(const Vector2D& speed, const Vector2D& acceleration) : speed(speed), acceleration(acceleration) 
    {}

    Vector2D speed;
    Vector2D acceleration;
};

class Horizontal_Gravity_Component : public Component
{
public:
    Horizontal_Gravity_Component(int x_gravityAcceleration) : x_gravityAcceleration(x_gravityAcceleration) {}
    int x_gravityAcceleration;
};

class Vertical_Gravity_Component : public Component
{
public:
    Vertical_Gravity_Component(int y_gravityAcceleration) : y_gravityAcceleration(y_gravityAcceleration) {}
    int y_gravityAcceleration;
};

class Texture_Component : public Component
{
public:
    Texture_Component(const Texture& texture) : texture(texture) {}
    const Texture& texture;
};

class Animation_Component : public Component
{
public:
    Animation_Component(const Animation& animation) : animation(animation) {}
    const Animation& animation;
};

class Texture_Set_Component : public Component
{
public:
    Texture_Set_Component(std::unordered_map<std::string, const Texture*> textureStates = {}) : textureStates(textureStates){}
    
    std::string currentTexture;
    const Texture* getCurrentTexture() const { return textureStates.at(currentTexture); }
    std::unordered_map<std::string, const Texture*> textureStates;
};

class Animation_Set_Component : public Component
{
public:
    Animation_Set_Component(std::unordered_map<std::string, const Animation*> animations = {}) : animations{animations}, currentAnimation{""} {}

    std::unordered_map<std::string, const Animation*> animations;
    std::string currentAnimation;
    const Animation* getCurrentAnimation() const { return animations.at(currentAnimation); }
};



void LoadRegisteryPresets(ComponentRegistery& componentRegistery, TextureManager& textureManager, SceneManager& sceneManager);

}