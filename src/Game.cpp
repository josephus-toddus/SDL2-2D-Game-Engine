#include "Game.hpp"

cpuEng::Game::Game(int width, int height, float fps, bool loggingMethod /*true -> terminal, false -> log file*/) :
    m_window{width, height},
    m_componentRegistery{},
    m_scenes{m_componentRegistery, [this](Code c){Log(c);}, [this](std::string_view str){Log(str);}},
    m_textures{[this](Code c){Log(c);}, [this](std::string_view str){Log(str);}},
    m_input{},
    m_events{m_window, m_input},
    m_logic{m_input, m_events},
    m_renderer{m_window, m_scenes},
    m_deltaTime{0.0f},
    m_timeSinceLastFrame{std::chrono::steady_clock::now()},
    m_file{},
    m_log{nullptr},
    m_fps{fps},
    m_OneFrameLength{1.0f / static_cast<float>(fps)}
{
    if (loggingMethod) {
        m_log = &std::cout;
    }
    else {
        std::filesystem::create_directory("log");
        m_file.open(std::format("log/{}.log", time(false)));
        m_log = &m_file;
    }

    Log("[Info---] Log created.");

    if (!IMG_Init(IMG_INIT_PNG)) {
        Log("[ERROR--] SDL Image failed to initialise with PNG.");
        this->~Game();
        return;
    }
    Log("[Info---] SDL Image initialised successfully with PNG.");

    SDL_AddEventWatch(&cpuEng::Game::ResizeWatch, this);

    // Maybe turn this into like an STL (not SDL, STL) of sorts? Yeah OK I kinda did it's just not organised.

    LoadRegisteryPresets(m_componentRegistery, m_textures, m_scenes);

}
void cpuEng::Game::MakeScene(const std::string& scene_name, const std::string& scene_file_path)
{
    m_textures.createNewScene(scene_name);

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
        return std::format("{:%Y-%m-%d___%H-%M}", std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
    }
    catch (const std::exception& e) {
        return std::format("UTC---{:%Y-%m-%d___%H-%M}", std::chrono::system_clock::now());
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

        case Code::TextureManager_SceneDoesNotExist_AddTexture:
            *m_log << "[ERROR--] Current scene does not exist. SRC: AddTexture.\n";
            return;
        case Code::TextureManager_SceneDoesNotExist_AddTextureAlwaysLoaded:
            *m_log << "[ERROR--] Current scene does not exist. SRC: AddTextureAlwaysLoaded.\n";
            return;
        case Code::TextureManager_TextureAlreadyExists_AddTexture:
            *m_log << "[Info---] The Texture already exists, nothing created or loaded. SRC: AddTexture.\n";
            return;
        case Code::TextureManager_TextureAlreadyExists_AddTextureAlwaysLoaded:
            *m_log << "[Info---] The Texture already exists, nothing created or loaded. SRC: AddTextureAlwaysLoaded.\n";
            return;
        case Code::TextureManager_AnimationHasNoFrames_AddAnimation:
            *m_log << "[ERROR--] Animation creation aborted: Animation has no frames. SRC: AddAnimation.\n";
            return;
        case Code::TextureManager_SceneDoesNotExist_AddAnimation:
            *m_log << "[ERROR--] Current scene does not exist. SRC: AddAnimation.\n";
            return;
        case Code::TextureManager_TextureAlreadyExists_AddAnimation:
            *m_log << "[Info---] The Texture already exists, nothing created or loaded. SRC: AddAnimation.\n";
            return;
        case Code::TextureManager_AnimationHasNoFrames_AddAnimationAlwaysLoaded:
            *m_log << "[ERROR--] Animation creation aborted: Animation has no frames. SRC: AddAnimationAlwaysLoaded.\n";
            return;
        case Code::TextureManager_TextureAlreadyExists_AddAnimationAlwaysLoaded:
            *m_log << "[Info---] The Texture already exists, nothing created or loaded. SRC: AddAnimationAlwaysLoaded.\n";
            return;
        case Code::TextureManager_SceneDoesNotExist_getTexture:
            *m_log << "[ERROR--] Current scene does not exist. SRC: getTexture.\n";
            return;
        case Code::TextureManager_TextureDoesNotExist_getTexture:
            *m_log << "[ERROR--] The Texture does not exists. SRC: getTexture.\n";
            return;
        case Code::TextureManager_TextureDoesNotExist_getTextureAlwaysLoaded:
            *m_log << "[ERROR--] The Texture does not exists. SRC: getTextureAlwaysLoaded.\n";
            return;
        case Code::TextureManager_SceneDoesNotExist_getAnimation:
            *m_log << "[ERROR--] Current scene does not exist. SRC: getAnimation.\n";
            return;
        case Code::TextureManager_TextureDoesNotExist_getAnimation:
            *m_log << "[ERROR--] The Texture does not exists. SRC: getAnimation.\n";
            return;
        case Code::TextureManager_TextureDoesNotExist_getAnimationAlwaysLoaded:
            *m_log << "[ERROR--] The Texture does not exists. SRC: getAnimationAlwaysLoaded.\n";
            return;
        case Code::TextureManager_SpecifiedSceneDoesNotExist_getTexture:
            *m_log << "[ERROR--] The specified scene does not exist. SRC: getTexture.\n";
            return;
        case Code::TextureManager_SpecifiedSceneDoesNotExist_getAnimation:
            *m_log << "[ERROR--] The specified scene does not exist. SRC: getAnimations.\n";
            return;

        case Code::TextureManager_SceneFailedToCreate_createNewScene:
            *m_log << "[ERROR--] The scene could not be inerted. SRC: TextureManager::createNewScene\n";
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
    m_OneFrameLength = std::chrono::duration<float>(1.0f / static_cast<float>(m_fps));
}

void cpuEng::Game::Loop()
{
    auto lastFrame = std::chrono::steady_clock::now();

    while (true) {

        auto frameStart = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(frameStart - lastFrame).count();
        
        lastFrame = frameStart;

        //      //   //////////  //   ////// //////////
        //      //   //          // //       //        
        //      //   //          ///         //        
        //////////   //////////  //          //////////
        //      //   //          //          //        
        //      //   //          //          //        
        //      //   //////////  //          //////////

        if (m_events.CheckEvents() == -1) {
            break;
        }


        RenderFrame();


        //      //   //////////  //   ////// //////////
        //      //   //          // //       //        
        //      //   //          ///         //        
        //////////   //////////  //          //////////
        //      //   //          //          //        
        //      //   //          //          //        
        //      //   //////////  //          //////////



        auto frameEnd = std::chrono::steady_clock::now();
        auto frameTime = frameEnd - frameStart;

        if (frameTime < m_OneFrameLength)
        {
            std::this_thread::sleep_for(
                m_OneFrameLength - frameTime
            );
        }
    }
    SDL_Quit();
}


// This is just a better way to Render frames in an organised way
void cpuEng::Game::RenderFrame()
{
    m_window.setBackGround(0xFFFFFFFF);
    // later: m_renderer draw calls go here
    m_window.upDateWindow();
}

// \
This is something that interjects before CheckEvents takes control and prevents drawing. \
Basically it makes sure the window doesn't look wierd when resizing

int SDLCALL cpuEng::Game::ResizeWatch(void* userdata, SDL_Event* e)
{
    if (e->type == SDL_WINDOWEVENT &&
        (e->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
         e->window.event == SDL_WINDOWEVENT_EXPOSED))
    {
        auto* self = static_cast<cpuEng::Game*>(userdata);
        self->m_window.Resize();   // resync the framebuffer to the new surface
        self->RenderFrame();       // draw + present immediately
    }
    return 0;
}


cpuEng::Game::~Game()
{
    SDL_DelEventWatch(&cpuEng::Game::ResizeWatch, this);
    IMG_Quit();
    SDL_Quit();
}