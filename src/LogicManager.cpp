#include "LogicManager.hpp"

cpuEng::LogicManager::LogicManager(std::vector<Entity>& entities, InputManager& inputManager, EventManager& eventManager) :
    m_entities{entities},
    m_inputManager{inputManager},
    m_eventManager{eventManager}
{}

void cpuEng::LogicManager::UpdateLogic(float deltaTime)
{
    UpdateContext updateContext{m_inputManager, m_eventManager, deltaTime};

    for (int i = 0; Entity& item : m_entities) {
        for (auto func : m_logic[i]) {
            func(item, updateContext);
        }
        ++i;
    }
}

void cpuEng::LogicManager::AddLogic(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func)
{
    m_logic[eid].push_back(func);
}