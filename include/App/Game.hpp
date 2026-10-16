#pragma once

#include "LogicManager.hpp"

#include "SceneManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

namespace cpuEng
{

class Game
{
public:

    Game(int width = 800, int height = 600);
    void MakeScene(const std::string& scene_name, const std::string& scene_file_path);
    void SetCurrentScene(const std::string& scene_name, const std::string& scene_file_path);
    void Update();

    void AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func);

private:
    Window m_window;

    SceneManager m_scenes;
    TextureManager m_textures;
    InputManager m_input;

    EventManager m_events;

    Renderer m_renderer;

    float deltaTime;

};

}