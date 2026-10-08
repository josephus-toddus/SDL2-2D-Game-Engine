#include "SceneManager.hpp"

const std::vector<std::unique_ptr<cpuEng::Entity>>& cpuEng::SceneManager::getCurrentEntites() const
{
    return m_current_scene->getEntities();
}
void cpuEng::SceneManager::switchScene(std::string scene)
{
    if (!m_scenes.contains(scene)) {
        assert(false && "The scene entered doesn't exist");
        return;
    }
    m_current_scene = &m_scenes[scene];
}

void cpuEng::SceneManager::newScene(std::string name, std::string filepath)
{

}