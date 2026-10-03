#include "Scene.hpp"

#pragma once

namespace cpuEng
{

class SceneManager
{
public:

    const std::vector<std::unique_ptr<Entity>>& getCurrentEntites();
    void switchScene(std::string scene);

    void newScene(std::string name, std::string filepath);

private:
    std::unordered_map<std::string, Scene> m_scenes;
    std::unordered_map<std::string, Scene>::iterator m_current_scene;
};

}