#pragma once

#include "LogicManager.hpp"

#include "SceneManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

#include <fstream>

#include "Codes.hpp"

namespace cpuEng
{

class Game
{
public:

    Game(int width = 800, int height = 600);
    void MakeScene(const std::string& scene_name, const std::string& scene_file_path);
    void SetCurrentScene(const std::string& scene_name);
    void Update();

    void AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func);

private:
    Window m_window;

    SceneManager m_scenes;
    TextureManager m_textures;
    InputManager m_input;

    EventManager m_events;

    LogicManager m_logic;

    Renderer m_renderer;

    float deltaTime;

    // logging stuff

    std::ofstream m_log;

    std::string time(bool format = true);

    void Log(Code code);
    void Log(std::string custom_message);


};

}