#pragma once

#include "Window.hpp"
#include "Entity.hpp"
#include "Scene.hpp"

namespace cpuEng
{

enum class CameraMode
{
    Static,     //waiting for an instruction, either to start travelling or tracking
    Travelling, //one time job to move
    Tracking    //tracking one entity
};


class Camera
{
public:

    Camera(float x, float y, bool isSmooth, float cameraSmoothness);


    void SetPos(float x, float y);
    void SetPos(const Entity& entity);

    void SetTarget(const Entity& target);

    const Position& GetPos() const;

    void Update(float deltaTime);

    void setCameraSmoothness(float cameraSmoothness);


private:

    Position m_pos;

    Position m_destination;

    CameraMode m_mode;

    bool m_smooth;

    //for following an Entity (that has PositionComponent)

    const Entity* m_target;
    float m_cameraSmoothness;

    //for direct smooth-move (like to a position or entity, one time travel rather than constantly following)

    Position m_startPos;        //Where the camera started moving from
    float m_totalMoveTime;      //The time the movement is set to take
    float m_sinceMovementStart; //The time that has elapsed since the start of movement
};

}