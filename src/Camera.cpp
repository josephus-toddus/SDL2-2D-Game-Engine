#include "Camera.hpp"
#include <algorithm>

cpuEng::Camera::Camera(const Scene& scene, float x, float y, bool isSmooth) :
    m_pos{x, y},
    m_destination{m_pos},
    m_mode{CameraMode::Static},
    m_smooth{isSmooth},
    m_target{nullptr},
    m_movement{0.0f, 0.0f},
    m_startPos{m_pos},
    m_totalMoveTime{0.0f},
    m_sinceMovementStart{0.0f}
{}

void cpuEng::Camera::SetPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}
void cpuEng::Camera::SetPos(const Entity& entity)
{
    const Position_Component* p = entity.GetComponent<Position_Component>();
    if (p) {
        m_pos.x = p->m_pos.x;
        m_pos.y = p->m_pos.y;
    }
}

void cpuEng::Camera::SetTarget(const Entity& target)
{
    if (!target.GetComponent<Position_Component>()) {
        return; // doesn't have a Position;
    }

    m_target = &target;
}

const cpuEng::Position& cpuEng::Camera::GetPos() const
{
    return m_pos;
}

void cpuEng::Camera::Update(float deltaTime)
{
    if (!m_target && m_mode == CameraMode::Tracking) {
        m_destination = m_target->GetComponent<Position_Component>()->m_pos;
    }

    if (m_smooth) {
        if (m_mode == CameraMode::Travelling) {
            m_sinceMovementStart += deltaTime;

            float progress = m_sinceMovementStart / m_totalMoveTime;
            progress = std::clamp(progress, 0.0f, 1.0f);

            float smoothProgress = 0.0f;

            if (progress < 0.5f) {
                smoothProgress = 2.0f * progress * progress;
            }
            else {
                smoothProgress = 1.0f - pow(-2.0f * progress + 2.0f, 2.0f) / 2.0f;
            }

            m_pos.x = m_startPos.x + (m_destination.x - m_startPos.x) * smoothProgress;
            m_pos.y = m_startPos.y + (m_destination.y - m_startPos.y) * smoothProgress;

            if (progress == 1.0f) {
                m_mode = CameraMode::Static;
            }
        }
        if (m_mode == CameraMode::Tracking) {

        }
    }
    else {
        m_movement = {0, 0};
        m_pos = m_destination;
        m_startPos = m_pos;
    }
}