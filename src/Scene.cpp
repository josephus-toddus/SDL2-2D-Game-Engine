#include "Scene.hpp"


cpuEng::Scene::Scene(const std::string& name, const std::string& filepath)
{

}

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::Scene::getEntities() const
{
    return m_entities;
}

const std::string& cpuEng::Scene::getName() const
{
    return m_name;
}