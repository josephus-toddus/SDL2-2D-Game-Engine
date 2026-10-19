#include "Game.hpp"

cpuEng::Game::Game(int width, int height, int fps, bool loggingMethod /*true -> terminal, false -> log file*/) :
    m_window{width, height},
    m_componentRegistery{},
    m_scenes{m_componentRegistery, [this](Code c){Log(c);} },
    m_textures{},
    m_input{},
    m_events{m_window, m_input},
    m_logic{m_input, m_events},
    m_renderer{m_window, m_scenes},
    m_deltaTime{0.0f},
    m_timeSinceLastFrame{std::chrono::steady_clock::now()},
    m_file{},
    m_log{nullptr},
    m_fps{fps},
    m_OneFrameLength{1000.0f / static_cast<float>(fps)}
{
    if (loggingMethod) {
        m_log = &std::cout;
        return;
    }

    std::filesystem::create_directory("log");
    m_file.open(std::format("log/{}.log", time(false)));
    m_log = &m_file;
}
void cpuEng::Game::MakeScene(const std::string& scene_name, const std::string& scene_file_path)
{
    switch (m_scenes.newScene(scene_name, scene_file_path)) {
        case 0:
            Log(Code::Scene_Init__SuccessfullyLoaded);
            return;
        case 1:
            Log(Code::Scene_Init__AlreadyExists);
            return;
        case 2:
            Log(Code::Scene_Init__ReadFailed);
            return;
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

    // Update the Game First

    // Limit the frame rate
    auto frameTimeLeft = m_OneFrameLength - (std::chrono::steady_clock::now() - m_timeSinceLastFrame);

    if (frameTimeLeft > std::chrono::steady_clock::duration::zero()) {
        std::this_thread::sleep_for(frameTimeLeft);
    }
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

// Log managing

void cpuEng::Game::Log(cpuEng::Code code)
{

    *m_log << time();

    switch (code) {


        case Code::Scene_Init__SuccessfullyLoaded:
            *m_log << "[Info---] Scene successfully loaded.\n";
            return;
        case Code::Scene_Init__AlreadyExists:
            *m_log << "[WARNING] Scene creation aborted: Already exists\n";
            return;
        case Code::Scene_Init__ReadFailed:
            *m_log << "[WARNING] Scene creation aborted: Reason unknown, look up in log\n";
            return;

        
        case Code::Scene_Change__SuccessfullyChanged:
            *m_log << "[Info---] Current scene Successfully changed.\n";
            return;
        case Code::Scene_Change__DoesNotExist:
            *m_log << "[WARNING] Current scene change aborted.\n";
            return;

        case Code::Scene_JSON__FileOpenFailed:
            *m_log << "[ERROR--] The specified JSON path could not be opened.\n";
            return;
        case Code::Scene_JSON__JSONSyntaxError:
            *m_log << "[WARNING] The specified JSON file is not syntactically correct.\n";
            return;
        case Code::Scene_JSON__EntityHasNoEID:
            *m_log << "[WARNING] JSON reader detected an Entity with no EID, Entity aborted.\n";
            return;
        case Code::Scene_JSON__FormattingWrong:
            *m_log << "[WARNING] JSON reader detected wrong formatting in the JSON. RTFM.\n";
            return;
        case Code::Scene_JSON__UnknownComponent:
            *m_log << "[WARNING] The component specified is unknown to the Component Registery, component aborted.\n";
            return;


        case Code::Scene_JSON__EmptyScene:
            *m_log << "[Info---] Scene is empty, check if intentional.\n";
            return;
        case Code::Scene_JSON__EntityHasNoComponents:
            *m_log << "[Info---] Entity has no components, check if intentional.\n";
            return;
        case Code::Scene_JSON__EntitySuccessfullyCreated:
            *m_log << "[Info---] Entity successfully created.\n";
            return;

        
        default:
            *m_log << "Unknown error.\n";
    }
}

void cpuEng::Game::Log(std::string_view custom_message)
{
    *m_log << time() << custom_message;
    if (custom_message.back() != '\n') {
        *m_log << '\n';
    }
}

void cpuEng::Game::SetTargetFPS(int fps)
{
    m_fps = fps;
    m_OneFrameLength = std::chrono::duration<float>(1000.0f / static_cast<float>(m_fps));
}