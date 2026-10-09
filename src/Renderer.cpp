#include "Renderer.hpp"
#include <span>

cpuEng::Renderer::Renderer(Window& window, const SceneManager& scenes) :
    m_window{window},
    m_scenes{scenes},
    m_camera{nullptr}
{
}

void cpuEng::Renderer::newCamera(std::string name, float x, float y, bool isSmooth, float cameraSmoothness)
{
    if (m_cameras.contains(name)) {
        return; // if the Renderer already has a camera in that name
    }
    m_cameras[name] = Camera(x, y, isSmooth, cameraSmoothness);
}
void cpuEng::Renderer::setCamera(std::string name)
{
    m_camera = &m_cameras.at(name);
}

void cpuEng::Renderer::RenderAll()
{
    const std::vector<std::unique_ptr<Entity>>& entities = m_scenes.getCurrentEntites();

    for (const std::unique_ptr<Entity>& entity : entities) {
        const Position_Component* positionComponent = entity->GetComponent<Position_Component>();

        if (positionComponent == nullptr) {
            continue;
        }

        const Texture_Component* textureComponent = entity->GetComponent<Texture_Component>();
        const Animation_Component* animationComponent = entity->GetComponent<Animation_Component>();
        if (!(textureComponent != nullptr) != (animationComponent != nullptr)) {
            continue;
        }
        if (textureComponent != nullptr) {
            std::vector<std::uint32_t*> textureRegion;

            Position windowPos {positionComponent->m_pos.x, positionComponent->m_pos.y};
            windowPos.x -= m_camera->GetPos().x;
            windowPos.y -= m_camera->GetPos().y;

            std::uint8_t overlap = IsInWindow
            (
                {windowPos.x, windowPos.y, textureComponent->texture.m_dim.width, textureComponent->texture.m_dim.width}, 
                {0.0f, 0.0f, m_window.m_width, m_window.m_height}
            );
            if (overlap == 0) { // Texture isn't even on the picture
                continue;
            }
            BoundingBox AvailibleTexture{0.0f, 0.0f, textureComponent->texture.m_dim.width, textureComponent->texture.m_dim.height};
            if (overlap == 1) {
                
            }

            textureRegion.reserve(textureComponent->texture.m_dim.height * textureComponent->texture.m_dim.width);
            for (int i = 0; i < textureComponent->texture.m_dim.height; ++i) {
                switch (overlap) {
                    case 1:  // The texture is partially on there (nightmare) Ok this is next now. I'm doing it. Not done tho

                        if (windowPos.x < 0) {
                            AvailibleTexture.x = -windowPos.x;
                            AvailibleTexture.width = textureComponent->texture.m_dim.width - AvailibleTexture.x;
                        }
                        if (windowPos.y < 0) {
                            AvailibleTexture.y = -windowPos.y;
                            AvailibleTexture.height = textureComponent->texture.m_dim.height - AvailibleTexture.y;
                        }

                        if (windowPos.x + textureComponent->texture.m_dim.width > m_window.m_width) {
                            AvailibleTexture.width = m_window.m_width - windowPos.x;
                        }
                        if (windowPos.y + textureComponent->texture.m_dim.height > m_window.m_height) {
                            AvailibleTexture.height = m_window.m_height - windowPos.y;
                        }

                        // SOMETHING IS STILL WRONG HERE PLS FIX IT
                        // please... ugh I can't do it now lemme commit and push before watching TV
                        


                        break;
                    case 2:  // The texture is completely on there (well it's OK, not that bad)

                        std::span<std::uint32_t> a(&m_window.m_pixels[windowPos.y * m_window.m_width + windowPos.x], textureComponent->texture.m_dim.width);
                        for (std::uint32_t& pixel : a) {
                            textureRegion.push_back(&pixel);
                        }
                        break;
                }
            }
            textureRegion.shrink_to_fit();

        }
        else {

        }
    }
}

std::uint8_t cpuEng::Renderer::IsInWindow(BoundingBox a, BoundingBox b)
{
    bool touching =
        a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y;
    
    bool within = 
        b.x >= a.x && 
        b.x + b.width <= a.x + a.width &&
        b.y >= a.y && 
        b.y + b.height <= a.y + a.height;

    return within ? 2 : touching ? 1 : 0;

}