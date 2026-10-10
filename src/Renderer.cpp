#include "Renderer.hpp"
#include <span>
#include <algorithm>

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
        const AnimationGroup_Component* animationGroupComponent = entity->GetComponent<AnimationGroup_Component>();
        const bool hasTexture = textureComponent != nullptr;
        const bool hasAnimation = animationComponent != nullptr;
        const bool hasAnimationGroup = animationGroupComponent != nullptr;

        if ((hasTexture + hasAnimation + hasAnimationGroup) != 1) { // if it has all three, two or none just skip
            continue;
        }

        const Texture* texture = nullptr;

        if (textureComponent != nullptr) {
            texture = &textureComponent->texture;
        }
        else if (animationComponent != nullptr) {
            texture = &animationComponent->animation.getCurrentTexture();
        }
        else if (animationGroupComponent != nullptr) {
            texture = &animationGroupComponent->currentAnimation->getCurrentTexture();
        }

        Position windowPos {positionComponent->m_pos.x, positionComponent->m_pos.y};
        windowPos.x -= m_camera->GetPos().x;
        windowPos.y -= m_camera->GetPos().y;

        BoundingBox AvailibleTexture{0.0f, 0.0f, static_cast<float>(texture->m_dim.width), static_cast<float>(textureComponent->texture.m_dim.height)};

        const int windowX = static_cast<int>(windowPos.x);
        const int windowY = static_cast<int>(windowPos.y);

        // Visible rectangle in window coordinates
        const int visibleLeft   = std::max(0, windowX);
        const int visibleTop    = std::max(0, windowY);
        const int visibleRight  = std::min(m_window.m_width, windowX + texture->m_dim.width);
        const int visibleBottom = std::min(m_window.m_height, windowY + texture->m_dim.height);

        AvailibleTexture.width = visibleRight - visibleLeft;
        AvailibleTexture.height = visibleBottom - visibleTop;

        if (AvailibleTexture.width <= 0 || AvailibleTexture.height <= 0) {
            continue;
        }

        // Corresponding rectangle in source-texture coordinates
        AvailibleTexture.x = visibleLeft - windowX;
        AvailibleTexture.y = visibleTop - windowY;

        // Creates a box which shows how much of the Texture can be drawn to the window safely

        const int AvailibleTextureY = static_cast<int>(AvailibleTexture.y);
        const int AvailibleTextureX = static_cast<int>(AvailibleTexture.x);
        const int AvailibleTextureHeight = static_cast<int>(AvailibleTexture.height);
        const int AvailibleTextureWidth = static_cast<int>(AvailibleTexture.width);

        const auto& rawTexture = *texture.getRawTexture(); ///DO SMTH HERE I GTG

        for (int i = 0; i < AvailibleTextureHeight; ++i) {
            std::span<std::uint32_t> a(
                &m_window.m_pixels[(visibleTop + i) * m_window.m_width + visibleLeft],
                AvailibleTextureWidth
            );
            for (int j = 0; j < AvailibleTextureWidth; ++j) {

                const std::uint32_t& pixel = rawTexture[(i + AvailibleTextureY) * texture->m_dim.width + j + AvailibleTextureX];
                std::uint32_t& oldPixel = a[j];

                std::uint8_t PixelA, PixelR, PixelG, PixelB;
                SDL_GetRGBA(pixel, m_window.m_surface->format, &PixelR, &PixelG, &PixelB, &PixelA);

                if (PixelA == 0) { 
                    continue;
                }
                if (PixelA == 255) {
                    a[j] = pixel;
                    continue;
                }

                std::uint8_t OldA, OldR, OldG, OldB;
                SDL_GetRGB(oldPixel, m_window.m_surface->format, &OldR, &OldG, &OldB);

                std::uint8_t NewA, NewR, NewG, NewB;

                const float PixelAlpha = static_cast<float>(PixelA) / 255.0f;

                NewR = PixelR * PixelAlpha + OldR * (1 - PixelAlpha);
                NewG = PixelG * PixelAlpha + OldG * (1 - PixelAlpha);
                NewB = PixelB * PixelAlpha + OldB * (1 - PixelAlpha);

                oldPixel = SDL_MapRGBA(m_window.m_surface->format, NewR, NewG, NewB, 255);
            }
        }
        
    }
}