#include "Animation.hpp"

cpuEng::Animation::Animation(const std::vector<Texture>& animation, int fps, bool shouldLoad) :
    m_animation(animation),
    m_frame(0),
    m_time(0),
    m_frame_duration(1.0 / static_cast<double>(fps)),
    isLoaded(false)
{
    if (shouldLoad) {
        load();
    }
}

cpuEng::Animation::Animation(const std::vector<std::string>& paths, int fps, bool shouldLoad) :
    m_animation(),
    m_frame(0),
    m_frame_duration(1.0 / static_cast<double>(fps)),
    isLoaded(false)
{
    bool successfully_loaded = true;
    for (int i = 0; i < paths.size(); ++i) {
        m_animation.push_back(Texture(paths[i], shouldLoad && successfully_loaded)); 
        // the && prevents loading textures when the loading has already failed for other Textures
        
        if (!m_animation[i].loaded()) {
            successfully_loaded = false;
        }
    }
    if (!successfully_loaded) {
        unload(); //unloads all the Textures that were loaded
    }

    isLoaded = successfully_loaded;
}

void cpuEng::Animation::Update (double deltaTime)
{
    m_time += deltaTime;
    if (m_time >= m_frame_duration) {
        int numberOfFrames = static_cast<int>(m_time / m_frame_duration);

        m_frame = (m_frame + numberOfFrames) % m_animation.size();

        m_time -= numberOfFrames * m_frame_duration;
    }
}

const cpuEng::Texture& cpuEng::Animation::getCurrentTexture()
{
    return m_animation[m_frame];
}

void cpuEng::Animation::load()
{
    bool loaded_successfully = true;

    for (Texture& t : m_animation) {
        t.load();
        if (!t.loaded()) {
            loaded_successfully = false;
            break;
        }
    }
    if (!loaded_successfully) {
        for (Texture& t : m_animation) {
            t.unload();
        }
        isLoaded = false;
        return;
    }
    isLoaded = true;
    return;
}

void cpuEng::Animation::unload()
{
    for (Texture& t : m_animation) {
        t.unload();
    }
    isLoaded = false;
}