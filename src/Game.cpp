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
void cpuEng::Game::MakeScene(const std::string& scene_name, const std::string& scene_file_path)
{

}
void cpuEng::Game::SetCurrentScene(const std::string& scene_name, const std::string& scene_file_path)
{

}
void cpuEng::Game::Update()
{

}

void cpuEng::Game::AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func)
{
    
}