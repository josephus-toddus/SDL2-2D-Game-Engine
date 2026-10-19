#include "Scene.hpp"

cpuEng::Scene::Scene() : 
    m_entities{},
    m_failedRead{true},
    Log{nullptr},
    LogStr{nullptr}
{

}

cpuEng::Scene::Scene(const std::string& filepath, const ComponentRegistery& componentRegistery, const std::function<void(const Code c)>& Log, const std::function<void(std::string_view)>& LogStr) :
    m_entities{},
    m_failedRead{true},
    Log{Log},
    LogStr{LogStr}
{
    // Init Scene to use filepath with json
    nlohmann::json file;            // The read json file
    std::ifstream input(filepath);  // Opening the file

    if (!input.is_open()) {
        Log(Code::Scene_JSON__FileOpenFailed);
        return;
    }
    try {
        input >> file;
    }
    catch (const nlohmann::json::parse_error& e) {
        Log(Code::Scene_JSON__JSONSyntaxError);
        return;
    }
    if (!file.contains("entities")|| 
        !file["entities"].is_array()) {
        
        Log(Code::Scene_JSON__EmptyScene);
        
        return;
    }

    for (std::uint64_t i = 0; i < file["entities"].size(); ++i) {

        const auto& entityData = file["entities"][i];

        if (!entityData.is_object()||
            !entityData.contains("eid") ||
            !entityData["eid"].is_number_unsigned()) {

            Log(Code::Scene_JSON__EntityHasNoEID);
            continue;
        }

        std::unique_ptr<Entity> entity = std::make_unique<Entity>(entityData["eid"].get<std::uint64_t>());

        if (!entityData.contains("components")) {
            m_entities.push_back(std::move(entity));

            Log(Code::Scene_JSON__EntityHasNoComponents);
            continue;
        }
        
        const auto& components = entityData["components"];
        
        if (!components.is_object()) {
            Log(Code::Scene_JSON__FormattingWrong);
            continue;
        }

        for (auto it = components.begin(); it != components.end(); ++it) {
            if (!it.value().is_object()) {
                Log(Code::Scene_JSON__FormattingWrong);
                continue;
            }

            try {
                componentRegistery.AddComponent(*entity, it.key(), it.value());
            }
            catch(const std::runtime_error& err) {
                LogStr(err.what());
            }
        }

        m_entities.push_back(std::move(entity));
        Log(Code::Scene_JSON__EntitySuccessfullyCreated);
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