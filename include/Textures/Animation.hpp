#include <Texture.hpp>

namespace cpuEng {

class Animation {
public:

    Animation(const std::vector<Texture>& animation, int fps, bool shouldLoad);
    Animation(const std::vector<std::string>& paths, int fps, bool shouldLoad);

    void Update (double deltaTime);

    const Texture& getCurrentTexture();

    void load();

    void unload();


private:
  
    std::vector<Texture> m_animation;

    int m_frame;
    double m_time;
    double m_frame_duration;
    bool isLoaded;
};

} // namespace cpuEng