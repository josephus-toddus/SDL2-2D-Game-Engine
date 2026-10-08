#include "Game.hpp"

cpuEng::Game::Game(int width, int height) :
    m_window{width, height},
    m_scenes{},
    m_textures{},
    m_input{},
    m_events{m_window, m_input},
    m_renderer{m_window, m_scenes}

{

}
void cpuEng::Game::MakeScene(const std::string& scene_name)
{

}
void cpuEng::Game::SetCurrentScene(const std::string& scene_name)
{

}
void cpuEng::Game::Update()
{

}