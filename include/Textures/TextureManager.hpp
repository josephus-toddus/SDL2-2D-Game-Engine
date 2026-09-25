#pragma once

#include "Animation.hpp"
#include <unordered_map>
#include <cassert>

namespace cpuEng {

class TextureManager {

public:

    TextureManager();

    void AddTexture(const std::string& path, const std::string& scene); // Uses path as the nickname
    void AddTexture(const std::string& path, const std::string& scene, const std::string& nickName); // shorthand to access easily
    
    void AddTextureAlwaysLoaded(const std::string& path);
    void AddTextureAlwaysLoaded(const std::string& path, const std::string& nickName);

    void AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene);
    void AddAnimation(const std::vector<std::string>& paths, int fps, const std::string& scene, const std::string& nickName);

    void AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps);
    void AddAnimationAlwaysLoaded(const std::vector<std::string>& paths, int fps, const std::string& nickName);

    //if the texture doesn't exist the function will assert and return a fallback texture
    const Texture& getTexture(const std::string& name /*the nickname*/) const; // uses the m_current_scene
    const Texture& getTextureAlwaysLoaded(const std::string& name) const;
    const Animation& getAnimation(const std::string& name /*the nickname*/) const; // same here
    const Animation& getAnimationAlwaysLoaded(const std::string& name) const;

    const Texture& getTexture(const std::string& scene, const std::string& name /*the nickname*/) const;
    const Animation& getAnimation(const std::string& scene, const std::string& name /*the nickname*/) const;

    void createNewScene(const std::string& scene);
    bool setCurrentScene(const std::string& scene);

private:

    std::unordered_map<std::string /*scene*/,
             std::unordered_map<std::string /*Texture name*/, Texture>>
        m_texture_scene_loaded;
    
    std::unordered_map<std::string /*scene*/,
             std::unordered_map<std::string /*Animation name*/, Animation>>
        m_animation_scene_loaded;


    std::unordered_map<std::string /*Texture name*/, Texture> m_texture_always_loaded;
    std::unordered_map<std::string /*Animation name*/, Animation> m_animation_always_loaded;

    Texture m_fallback;
    Animation m_animation_fallback;

    std::string m_current_scene;
};

}