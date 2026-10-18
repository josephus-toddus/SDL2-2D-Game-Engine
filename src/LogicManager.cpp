#include "LogicManager.hpp"

cpuEng::LogicManager::LogicManager(InputManager& inputManager, EventManager& eventManager, std::vector<Entity>* entities) :
    m_entities{entities},
    m_inputManager{inputManager},
    m_eventManager{eventManager}
{}

void cpuEng::LogicManager::UpdateLogic(float deltaTime)
{
    UpdateContext updateContext{m_inputManager, m_eventManager, deltaTime};

    for (Entity& item : *m_entities) {
        for (auto func : m_logic[item.m_eid]) {
            func(item, updateContext);
        }
    }


}

void cpuEng::LogicManager::AddLogic(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func)
{
    m_logic[eid].push_back(func);
}