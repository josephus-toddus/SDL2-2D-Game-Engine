#pragma once

#include "Camera.hpp"
#include "SceneManager.hpp"

namespace cpuEng
{

class Renderer
{
public:
    Renderer(Window& window, const SceneManager& scenes);

    void newCamera(std::string name, float x, float y, bool isSmooth = true, float cameraSmoothness = 0.05f);
    void setCamera(std::string name);

    void RenderAll();

private:
    const Camera* m_camera;

    Window& m_window;
    std::unordered_map<std::string, Camera> m_cameras;

    const SceneManager& m_scenes;
};

}