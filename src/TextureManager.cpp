#include "TextureManager.hpp"
#include <format>

cpuEng::TextureManager::TextureManager() :
    m_fallback({0x0, 0x00F800F8, 0x0, 0x00F800F8}, {2, 2}),
    m_animation_fallback({m_fallback}, 1, true)
{
}

void cpuEng::TextureManager::AddTexture(const std::string& path, const std::string& scene)
{
    AddTexture(path, scene, path);
}
void cpuEng::TextureManager::AddTexture(const std::string& path, const std::string& scene, const std::string& nickName)
{
    if (!m_texture_scene_loaded.contains(scene)) {
        assert(false && "The scene entered does not exist");
        return;
    }
    m_texture_scene_loaded.at(scene)[nickName] = Texture(path, m_current_scene == scene);
}

void cpuEng::TextureManager::AddTextureAlwaysLoaded(const std::string& path)
{
    AddTextureAlwaysLoaded(path, path);
}
void cpuEng::TextureManager::AddTextureAlwaysLoaded(const std::string& path, const std::string& nickName)
{
    m_texture_always_loaded[nickName] = Texture(path, true);
}

void cpuEng::TextureManager::AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene)
{
    if (paths.empty()) {
        assert(false && "An animation needs at least one frame");
        return;
    }
    AddAnimation(paths, fps, scene, paths[0]);
}
void cpuEng::TextureManager::AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene, const std::string& nickName)
{
    if (paths.empty()) {
        assert(false && "An animation needs at least one frame");
        return;
    }
    if (!m_animation_scene_loaded.contains(scene)) {
        assert(false && "The scene entered does not exist");
        return;
    }
    m_animation_scene_loaded.at(scene)[nickName] = Animation(paths, fps, m_current_scene == scene);
}

void cpuEng::TextureManager::AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps)
{
    if (paths.empty()) {
        assert(false && "An animation needs at least one frame");
        return;
    }
    AddAnimationAlwaysLoaded(paths, fps, paths[0]);
}
void cpuEng::TextureManager::AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps, const std::string& nickName)
{
    if (paths.empty()) {
        assert(false && "An animation needs at least one frame");
        return;
    }
    m_animation_always_loaded[nickName] = Animation(paths, fps, true);
}


const cpuEng::Texture& cpuEng::TextureManager::getTexture(const std::string& name) const
{
    if (!m_texture_scene_loaded.contains(m_current_scene)) {
        assert(false && "'m_texture_scene_loaded' does not contain 'm_current_scene'");
        return m_fallback;
    }
    if (!m_texture_scene_loaded.at(m_current_scene).contains(name)) {
        assert(false && "'m_texture_scene_loaded[m_current_scene]' does not contain 'name'");
        return m_fallback;
    }
    return m_texture_scene_loaded.at(m_current_scene).at(name);
}
const cpuEng::Texture& cpuEng::TextureManager::getTextureAlwaysLoaded(const std::string& name) const
{
    if (!m_texture_always_loaded.contains(name)) {
        assert(false && "'m_textures_always_loaded' does not contain 'name'");
        return m_fallback;
    }
    return m_texture_always_loaded.at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimation(const std::string& name) const
{
    if (!m_animation_scene_loaded.contains(m_current_scene)) {
        assert(false && "'m_animation_scene_loaded' does not contain 'm_current_scene'");
        return m_animation_fallback;
    }
    if (!m_animation_scene_loaded.at(m_current_scene).contains(name)) {
        assert(false && "'m_animation_scene_loaded[m_current_scene]' does not contain 'name'");
        return m_animation_fallback;
    }
    return m_animation_scene_loaded.at(m_current_scene).at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimationAlwaysLoaded(const std::string& name) const
{
    if (!m_animation_always_loaded.contains(name)) {
        assert(false && "'m_animation_always_loaded' does not contain 'name'");
        return m_animation_fallback;
    }
    return m_animation_always_loaded.at(name);
}

const cpuEng::Texture& cpuEng::TextureManager::getTexture(const std::string& scene, const std::string& name) const
{
    if (!m_texture_scene_loaded.contains(scene)) {
        assert(false && "'m_texture_scene_loaded' does not contain 'scene'");
        return m_fallback;
    }
    if (!m_texture_scene_loaded.at(scene).contains(name)) {
        assert(false && "'m_texture_scene_loaded[scene]' does not contain 'name'");
        return m_fallback;
    }
    return m_texture_scene_loaded.at(scene).at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimation(const std::string& scene, const std::string& name) const
{
    if (!m_animation_scene_loaded.contains(scene)) {
        assert(false && "'m_animation_scene_loaded' does not contain 'scene'");
        return m_animation_fallback;
    }
    if (!m_animation_scene_loaded.at(scene).contains(name)) {
        assert(false && "'m_animation_scene_loaded[scene]' does not contain 'name'");
        return m_animation_fallback;
    }
    return m_animation_scene_loaded.at(scene).at(name);
}

void cpuEng::TextureManager::createNewScene(const std::string& scene)
{
    m_texture_scene_loaded.try_emplace(scene);
    m_animation_scene_loaded.try_emplace(scene);
}

bool cpuEng::TextureManager::setCurrentScene(const std::string& scene)
{
    if (!m_texture_scene_loaded.contains(scene) || !m_animation_scene_loaded.contains(scene)) { 
        // I'm keeping both as a safety, though in theory one would be fine
        return false;
    }

    if (m_current_scene == scene) {
        return true;
    }

    // unload all current scene textures and load all the new ones

    if (!m_current_scene.empty()) {
        for (auto& [name, texture] : m_texture_scene_loaded.at(m_current_scene)) {
            texture.unload();
        }
        for (auto& [name, animation] : m_animation_scene_loaded.at(m_current_scene)) {
            animation.unload();
        }
    }

    for (auto& [name, texture] : m_texture_scene_loaded.at(scene)) {
        texture.load();
    }

    for (auto& [name, animation] : m_animation_scene_loaded.at(scene)) {
        animation.load();
    }
    
    m_current_scene = scene;
    return true;
}