#pragma once

#include "SceneManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "EventManager.hpp"

namespace cpuEng
{

class Game
{
public:

    Game(int width = 800, int height = 600);
    void MakeScene(const std::string& scene_name);
    void SetCurrentScene(const std::string& scene_name);
    void Update();

private:
    Window m_window;

    SceneManager m_scenes;
    TextureManager m_textures;
    InputManager m_input;

    EventManager m_events;

    Renderer m_renderer;

    double deltaTime;

};

}