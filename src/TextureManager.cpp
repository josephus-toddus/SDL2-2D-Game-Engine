#include "TextureManager.hpp"
#include <format>

void cpuEng::TextureManager::AddTexture(const std::string& path, const std::string& scene)
{
    AddTexture(path, scene, path);
}
void cpuEng::TextureManager::AddTexture(const std::string& path, const std::string& scene, const std::string& nickName)
{
    if (!m_texture_scene_loaded.contains(scene)) {
        Log(Code::TextureManager_SceneDoesNotExist_AddTexture);
        return;
    }
    if (m_texture_scene_loaded.at(scene).contains(nickName)) {
        Log(Code::TextureManager_TextureAlreadyExists_AddTexture);
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
    if (m_texture_always_loaded.contains(nickName)) {
        Log(Code::TextureManager_TextureAlreadyExists_AddTextureAlwaysLoaded);
        return;
    }
    m_texture_always_loaded[nickName] = Texture(path, true);
}

void cpuEng::TextureManager::AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene)
{
    if (paths.empty()) {
        Log(Code::TextureManager_AnimationHasNoFrames_AddAnimation);
        return;
    }
    AddAnimation(paths, fps, scene, paths[0]);
}
void cpuEng::TextureManager::AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene, const std::string& nickName)
{
    if (paths.empty()) {
        Log(Code::TextureManager_AnimationHasNoFrames_AddAnimation);
        return;
    }
    if (!m_animation_scene_loaded.contains(scene)) {
        Log(Code::TextureManager_SceneDoesNotExist_AddAnimation);
        return;
    }
    if (m_animation_scene_loaded.at(scene).contains(nickName)) {
        Log(Code::TextureManager_TextureAlreadyExists_AddAnimation);
        return;
    }
    m_animation_scene_loaded.at(scene)[nickName] = Animation(paths, fps, m_current_scene == scene);
}

void cpuEng::TextureManager::AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps)
{
    if (paths.empty()) {
        Log(Code::TextureManager_AnimationHasNoFrames_AddAnimationAlwaysLoaded);
        return;
    }
    AddAnimationAlwaysLoaded(paths, fps, paths[0]);
}
void cpuEng::TextureManager::AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps, const std::string& nickName)
{
    if (paths.empty()) {
        Log(Code::TextureManager_AnimationHasNoFrames_AddAnimationAlwaysLoaded);
        return;
    }
    if (m_animation_always_loaded.contains(nickName)) {
        Log(Code::TextureManager_TextureAlreadyExists_AddAnimationAlwaysLoaded);
        return;
    }
    m_animation_always_loaded[nickName] = Animation(paths, fps, true);
}


const cpuEng::Texture& cpuEng::TextureManager::getTexture(const std::string& name) const
{
    if (!m_texture_scene_loaded.contains(m_current_scene)) {
        Log(Code::TextureManager_SceneDoesNotExist_getTexture); // I believe this is where it fails. Ig it's fine, m_fallback is returned but still, not very promising
        return m_fallback;
    }
    if (!m_texture_scene_loaded.at(m_current_scene).contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getTexture);
        return m_fallback;
    }
    return m_texture_scene_loaded.at(m_current_scene).at(name);
}
const cpuEng::Texture& cpuEng::TextureManager::getTextureAlwaysLoaded(const std::string& name) const
{
    if (!m_texture_always_loaded.contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getTextureAlwaysLoaded);
        return m_fallback;
    }
    return m_texture_always_loaded.at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimation(const std::string& name) const
{
    if (!m_animation_scene_loaded.contains(m_current_scene)) {
        Log(Code::TextureManager_SceneDoesNotExist_getAnimation);
        return m_animation_fallback;
    }
    if (!m_animation_scene_loaded.at(m_current_scene).contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getAnimation);
        return m_animation_fallback;
    }
    return m_animation_scene_loaded.at(m_current_scene).at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimationAlwaysLoaded(const std::string& name) const
{
    if (!m_animation_always_loaded.contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getAnimationAlwaysLoaded);
        return m_animation_fallback;
    }
    return m_animation_always_loaded.at(name);
}

const cpuEng::Texture& cpuEng::TextureManager::getTexture(const std::string& scene, const std::string& name) const
{
    if (!m_texture_scene_loaded.contains(scene)) {
        Log(Code::TextureManager_SpecifiedSceneDoesNotExist_getTexture);
        return m_fallback;
    }
    if (!m_texture_scene_loaded.at(scene).contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getTexture);
        return m_fallback;
    }
    return m_texture_scene_loaded.at(scene).at(name);
}
const cpuEng::Animation& cpuEng::TextureManager::getAnimation(const std::string& scene, const std::string& name) const
{
    if (!m_animation_scene_loaded.contains(scene)) {
        Log(Code::TextureManager_SpecifiedSceneDoesNotExist_getAnimation);
        return m_animation_fallback;
    }
    if (!m_animation_scene_loaded.at(scene).contains(name)) {
        Log(Code::TextureManager_TextureDoesNotExist_getAnimation);
        return m_animation_fallback;
    }
    return m_animation_scene_loaded.at(scene).at(name);
}

void cpuEng::TextureManager::createNewScene(const std::string&scene)
{
    if (!m_texture_scene_loaded.try_emplace(scene).second || !m_animation_scene_loaded.try_emplace(scene).second) {
        Log(Code::TextureManager_SceneFailedToCreate_createNewScene);
    }
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

    if (!m_texture_scene_loaded[m_current_scene].empty()) {
        for (auto& [name, texture] : m_texture_scene_loaded.at(m_current_scene)) {
            texture.unload();
        }
    }
    if (!m_animation_scene_loaded[m_current_scene].empty()) {
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