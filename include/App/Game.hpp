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

private:
    Window m_window;

    SceneManager m_scenes;
    TextureManager m_textures;

    EventManager m_events;

    Renderer m_renderer;

    double deltaTime;

};

}