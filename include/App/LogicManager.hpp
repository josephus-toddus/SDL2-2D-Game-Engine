#pragma once

#include "Entity.hpp"
#include "InputManager.hpp"
#include "EventManager.hpp"
#include <functional>

namespace cpuEng 
{

struct UpdateContext
{
    InputManager& input;
    EventManager& event;

    const float deltaTime;
};


class LogicManager
{
public:

    LogicManager(InputManager& inputManager, EventManager& eventManager, std::vector<Entity>* entities = nullptr);

    

    void UpdateLogic(float deltaTime);

    void AddLogic(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func);

private:

    std::vector<Entity>* m_entities;
    InputManager& m_inputManager;
    EventManager& m_eventManager;

    std::vector<std::vector<std::function<void(Entity& currentEntity, UpdateContext& updateContext)>>> m_logic;

};



}