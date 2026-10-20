#include "SceneManager.hpp"
#include <algorithm>

std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::SceneManager::getCurrentEntites()
{
    if (m_current_scene != nullptr) {
        return m_current_scene->getEntities();
    }
    return m_fallbackEntities;
}
bool cpuEng::SceneManager::switchScene(std::string scene)
{
    auto it = m_scenes.find(scene);

    if (it == m_scenes.end()) {
        return false;
    }
    m_current_scene = &it->second;
    m_current_scene_name = &it->first;
    return true;
}

int cpuEng::SceneManager::newScene(std::string name, std::string filepath)
{
    if (m_scenes.contains(name)) { // already exists
        return 1;
    }

    m_loadingScene = name;
    
    m_scenes.insert({name, Scene(filepath, m_componentRegistery, Log, LogStr)});

    if (m_scenes[name].failedRead()) { // .json file read failed 
        return 2;
    }
    return 0;
}

const std::string& cpuEng::SceneManager::getCurrentSceneName() const
{
    if (m_current_scene_name == nullptr) {
        return m_loadingScene;
    }
    return *m_current_scene_name;
}

const std::string& cpuEng::SceneManager::getLoadingSceneName() const
{
    return m_loadingScene;
}

const cpuEng::Entity& cpuEng::SceneManager::getEntityFromEID(std::uint64_t eid)
{
    
    auto it = std::find_if(getCurrentEntites().begin(), getCurrentEntites().end(), [&eid](std::unique_ptr<Entity>& a){
        if (a->m_eid == eid) {
            return true;
        }
        return false;
    });

    if (it == getCurrentEntites().end()) {
        throw -1;
    }

    return **it;

    
}