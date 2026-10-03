#include "SceneManager.hpp"

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::SceneManager::getCurrentEntites()
{
    return m_current_scene->second.getEntities();
}
void cpuEng::SceneManager::switchScene(std::string scene)
{
    if (!m_scenes.contains(scene)) {
        assert(false && "The scene entered doesn't exist");
        return;
    }
}

void cpuEng::SceneManager::newScene(std::string name, std::string filepath)
{

}