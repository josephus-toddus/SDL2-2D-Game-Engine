#include "Animation.hpp"
#include <queue>

namespace cpuEng
{

class TextureAtlas
{
public:
    TextureAtlas(Texture& Texture);

    Texture getRegion(int x, int y, int width, int height);

private:
    std::queue<std::pair<std::string, Texture>> m_Textures;
    std::queue<std::pair<std::string, Animation>> m_Textures;

    //huh? why tf would I want a queue???
    
};

}