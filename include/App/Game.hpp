#pragma once

#include "LogicManager.hpp"

#include "SceneManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "ComponentPresets.hpp"

#include <fstream>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <thread>

#include "Codes.hpp"

namespace cpuEng
{

class Game
{
public:

    Game(int width = 800, int height = 600, float fps = 60.0f, bool loggingMethod = false);
    ~Game();

    void MakeScene(const std::string& scene_name, const std::string& scene_file_path);
    void SetCurrentScene(const std::string& scene_name);
    void Update();

    void AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func);

    void SetTargetFPS(int fps);

    void Loop();

    void RenderFrame();
    static int SDLCALL ResizeWatch(void* userdata, SDL_Event* e);

private:

    Window m_window;

    ComponentRegistery m_componentRegistery;
    SceneManager m_scenes;
    TextureManager m_textures;
    InputManager m_input;

    EventManager m_events;

    LogicManager m_logic;

    Renderer m_renderer;

    float m_deltaTime;
    std::chrono::steady_clock::time_point m_timeSinceLastFrame;

    // logging stuff

    std::ofstream m_file;
    std::ostream* m_log;

    float m_fps;
    std::chrono::duration<float> m_OneFrameLength;


    std::string time(bool format = true);

    void Log(Code code);
    void Log(std::string_view custom_message);


};

}