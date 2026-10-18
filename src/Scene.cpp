#include "Scene.hpp"

cpuEng::Scene::Scene() : 
    m_entities{},
    m_failedRead{true}
{

}

cpuEng::Scene::Scene(const std::string& filepath, const ComponentRegistery& componentRegistery) :
    m_entities{},
    m_failedRead{true}
{
    // Init Scene to use filepath with json
    nlohmann::json file;            // The read json file
    std::ifstream input(filepath);  // Opening the file

    if (!input.is_open()) {
        // Log file-opening error
        return;
    }
    try {
        input >> file;
    }
    catch (const nlohmann::json::parse_error& e) {
        // Log JSON parsing error
        return;
    }
    if (!file.contains("entities")|| 
        !file["entities"].is_array()) {
        return;
    }

    for (std::uint64_t i = 0; i < file["entities"].size(); ++i) {

        const auto& entityData = file["entities"][i];

        if (!entityData.is_object()||
            !entityData.contains("eid") ||
            !entityData["eid"].is_number_unsigned()) {
            // Log this somehow
            continue;
        }

        std::unique_ptr<Entity> entity = std::make_unique<Entity>(entityData["eid"].get<std::uint64_t>());

        if (!entityData.contains("components")) {
            // Log this somehow, this is fine, just means no components
            m_entities.push_back(std::move(entity));
            continue;
        }
        const auto& components = entityData["components"];
        
        if (!components.is_object()) {
            // Same but different log
            continue;
        }

        for (auto it = components.begin(); it != components.end(); ++it) {
            if (!it.value().is_object()) {
                // Log this somehow
                continue;
            }

            try {
                componentRegistery.AddComponent(*entity, it.key(), it.value());
            }
            catch(const std::runtime_error& err) {
                // Somehow log the fact the component doesn't exist.
            }
        }

        m_entities.push_back(std::move(entity));
    }

    m_failedRead = false; 
    // I'm considering that as long as the json was successfully read,
    // it was successful, any other errors or warning will be visible in the log when I implement that.
}

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::Scene::getEntities() const
{
    return m_entities;
}

bool cpuEng::Scene::failedRead() 
{
    return m_failedRead;
}