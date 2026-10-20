#pragma once

#include "Camera.hpp"
#include "SceneManager.hpp"

namespace cpuEng
{

class Renderer
{
public:
    Renderer(Window& window, const SceneManager& scenes);

    void newCamera(const std::string& name, float x, float y, bool isSmooth, float cameraSmoothness);
    void setCamera(const std::string& name);

    void RenderAll();

private:
    const Camera* m_camera;

    Window& m_window;
    std::unordered_map<std::string, Camera> m_cameras;

    const SceneManager& m_scenes;

    Texture m_fallback;
};

}