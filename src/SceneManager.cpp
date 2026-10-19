#include "SceneManager.hpp"

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::SceneManager::getCurrentEntites() const
{
    return m_current_scene->getEntities();
}
bool cpuEng::SceneManager::switchScene(std::string scene)
{
    if (!m_scenes.contains(scene)) {
        return false;
    }
    m_current_scene = &m_scenes[scene];
    return true;
}

int cpuEng::SceneManager::newScene(std::string name, std::string filepath)
{
    if (m_scenes.contains(name)) { // already exists
        return 1;
    }
    
    m_scenes.insert({name, Scene(filepath, m_componentRegistery, Log)});

    if (m_scenes[name].failedRead()) { // .json file read failed 
        return 2;
    }
    return 0;
}