#pragma once

#include "Camera.hpp"

namespace cpuEng
{

class Renderer
{

    void RenderEntity(const Entity& entity);

private:
    Camera m_camera;
    Window m_window;
};

}