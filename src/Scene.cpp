#include "Scene.hpp"

cpuEng::Scene::Scene() : 
    m_entities{},
    m_failedRead{true}
{

}

cpuEng::Scene::Scene(const std::string& filepath) :
    m_entities{},
    m_failedRead{true}
{
    // Init Scene to use filepath with json
}

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::Scene::getEntities() const
{
    return m_entities;
}

bool cpuEng::Scene::failedRead() 
{
    return m_failedRead;
}