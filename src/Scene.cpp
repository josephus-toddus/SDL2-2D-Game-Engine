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
    nlohmann::json file = nlohmann::json::parse(filepath);

    if (!file.contains("entities")) {
        return;
    }

    std::vector<std::uint64_t> entityIDs = file["entities"].get<std::vector<std::uint64_t>>();

    for (std::uint64_t item : entityIDs) {
        m_entities.push_back(std::make_unique<Entity>(item));
    }
}

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::Scene::getEntities() const
{
    return m_entities;
}

bool cpuEng::Scene::failedRead() 
{
    return m_failedRead;
}