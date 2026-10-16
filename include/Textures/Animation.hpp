#pragma once

#include <Texture.hpp>

namespace cpuEng {

class Animation {
public:

    Animation();
    Animation(const std::vector<Texture>& animation, int fps, bool shouldLoad);
    Animation(const std::vector<std::string>& paths, int fps, bool shouldLoad);

    void Update (float deltaTime);

    const Texture& getCurrentTexture() const;

    void load();

    void unload();


private:
  
    std::vector<Texture> m_animation;

    int m_frame;
    float m_time;
    float m_frame_duration;
    bool isLoaded;
};

} // namespace cpuEng