#include "Scene.hpp"

#pragma once

namespace cpuEng
{

class SceneManager
{
public:

    SceneManager(const ComponentRegistery& compReg);

    const std::vector<std::unique_ptr<Entity>>& getCurrentEntites() const;
    bool switchScene(std::string scene);

    int newScene(std::string name, std::string filepath); // returns 0 if successful, 1 if already exists and 2 if json reading failed

private:

    const ComponentRegistery& m_componentRegistery;
    std::unordered_map<std::string, Scene> m_scenes;
    const Scene* m_current_scene;
};

}