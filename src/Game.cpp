#include "Game.hpp"

#include <chrono>

cpuEng::Game::Game(int width, int height) :
    m_window{width, height},
    m_scenes{},
    m_textures{},
    m_input{},
    m_events{m_window, m_input},
    m_logic{m_input, m_events},
    m_renderer{m_window, m_scenes}
    ,m_log(std::format("log/log_{}.txt", time(false)))
{

}
void cpuEng::Game::MakeScene(const std::string& scene_name, const std::string& scene_file_path)
{
    switch (m_scenes.newScene(scene_name, scene_file_path)) {
        case 0:
            Log(Code::Scene_Init__SuccessfullyLoaded);
            break;
        case 1:
            Log(Code::Scene_Init__AlreadyExists);
            break;
        case 2:
            Log(Code::Scene_Init__ReadFailed);
            break;
    }
}
void cpuEng::Game::SetCurrentScene(const std::string& scene_name)
{
    if (!m_scenes.switchScene(scene_name)) {
        Log(Code::Scene_Change__DoesNotExist);
        return;
    }
    Log(Code::Scene_Change__SuccessfullyChanged);

}
void cpuEng::Game::Update()
{

}

void cpuEng::Game::AddLogicToEntity(std::uint64_t eid, std::function<void(Entity& currentEntity, UpdateContext& updateContext)> func)
{
    m_logic.AddLogic(eid, func);
}

std::string cpuEng::Game::time(bool format) {
    if (format) {
        try {
            return std::format("[{:%Y-%m-%d_%H:%M}]    ", std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
        }
        catch (const std::exception& e) {
            return std::format("[UTC: {:%Y-%m-%d_%H:%M}]    ", std::chrono::system_clock::now());
        }
    }
    try {
        return std::format("{:%Y-%m-%d_%H:%M:%S}", std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
    }
    catch (const std::exception& e) {
        return std::format("{:%Y-%m-%d_%H:%M:%S}", std::chrono::system_clock::now());
    }
}

void cpuEng::Game::Log(cpuEng::Code code)
{

    m_log << time();

    switch (code) {


        case Code::Scene_Init__SuccessfullyLoaded:
            m_log << "Scene successfully loaded.\n";
            return;
        case Code::Scene_Init__AlreadyExists:
            m_log << "Scene creation aborted. (SC-I_1)\n";
            return;
        case Code::Scene_Init__ReadFailed:
            m_log << "Scene creation aborted. (SC-I_2)\n";
            return;

        
        case Code::Scene_Change__SuccessfullyChanged:
            m_log << "Current scene Successfully changed.\n";
            return;
        case Code::Scene_Change__DoesNotExist:
            m_log << "Current scene change aborted. (SC-C_1)\n";
            return;

        
        default:
            m_log << "Unknown error. (UNK-9999)\n";
    }
}
void cpuEng::Game::Log(std::string custom_message)
{
    if (custom_message.back() != '\n') {
        custom_message.append("\n");
    }
    m_log << time() << custom_message;
}