#pragma once

#include "Camera.hpp"
#include "SceneManager.hpp"

namespace cpuEng
{

class Renderer
{
public:
    Renderer(Window& window, SceneManager& scenes);

    void newCamera(const std::string& name, const Position& pos, bool isSmooth, float cameraSmoothness);
    void setCamera(const std::string& name);

    void teleportCamera(const Position& pos);

    void teleportCamera(const Entity& entity);

    void setCameraTarget(const Entity& target);

    void CameraUpdate(float deltaTime);

    void RenderAll();

private:
    Camera* m_camera;

    Window& m_window;
    std::unordered_map<std::string, Camera> m_cameras;

    SceneManager& m_scenes;

    Texture m_fallback;
};

}