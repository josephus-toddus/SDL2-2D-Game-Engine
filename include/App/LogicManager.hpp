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

    LogicManager(InputManager& inputManager, EventManager& eventManager, std::vector<std::unique_ptr<Entity>>* entities = nullptr);

    

    void UpdateLogic(float deltaTime);

    void AddLogic(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func);

    void SetEntities(std::vector<std::unique_ptr<Entity>>* entities);

private:

    std::vector<std::unique_ptr<Entity>>* m_entities;
    InputManager& m_inputManager;
    EventManager& m_eventManager;

    std::unordered_map<std::uint64_t, std::vector<std::function<void(Entity& currentEntity, UpdateContext& updateContext)>>> m_logic;

};



}