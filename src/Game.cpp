#include "Game.hpp"

#include <chrono>

cpuEng::Game::Game(int width, int height) :
    m_window{width, height},
    m_scenes{},
    m_textures{},
    m_input{},
    m_events{m_window, m_input},
    m_logic{m_input, m_events},
    m_renderer{m_window, m_scenes},
    m_log(std::format("log/log_{:%Y%m%d_%H%M}.txt", std::chrono::system_clock::now()))
{

}
void cpuEng::Game::MakeScene(const std::string& scene_name, const std::string& scene_file_path)
{
    if (m_scenes.newScene(scene_name, scene_file_path) != 0) {
        m_log << time() << "Scene " << scene_name << " already exists, scene creation aborted.\n";
        return;
    }
    m_log << time() << "Scene " << scene_name << "successfully set to current scene.\n";
}
void cpuEng::Game::SetCurrentScene(const std::string& scene_name)
{
    if (!m_scenes.switchScene(scene_name)) {
        m_log << time() << "Scene " << scene_name << " does not exist, scene change aborted.\n";
        return;
    }
    m_log << time() << "Scene " << scene_name << "successfully set to current scene.\n";

}
void cpuEng::Game::Update()
{

}

void cpuEng::Game::AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func)
{
    m_logic.AddLogic(eid, func);
}

std::string cpuEng::Game::time() {

    try {
        return std::format("[{:%Y-%m-%d_%H:%M:%S}]    ", std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
    }
    catch (const std::exception& e) {
        return std::format("[UTC: {:%Y-%m-%d_%H:%M:%S}]    ", std::chrono::system_clock::now());
    }

}