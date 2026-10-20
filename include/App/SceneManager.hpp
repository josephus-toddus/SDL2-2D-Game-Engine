#include "Scene.hpp"

#pragma once

namespace cpuEng
{

class SceneManager
{
public:

    template <typename F, typename F2>
    SceneManager(const ComponentRegistery& compReg, F&& func, F2&& func2) :
        m_componentRegistery{compReg},
        Log(std::forward<F>(func)),
        LogStr(std::forward<F2>(func2)),
        m_current_scene{nullptr},
        m_current_scene_name{nullptr},
        m_loadingScene{""},
        m_fallbackEntities{std::vector<std::unique_ptr<Entity>>(1)}
    {}

    std::vector<std::unique_ptr<Entity>>& getCurrentEntites();
    bool switchScene(std::string scene);

    int newScene(std::string name, std::string filepath); // returns 0 if successful, 1 if already exists and 2 if json reading failed

    const std::string& getCurrentSceneName() const;
    const std::string& getLoadingSceneName() const;

    const Entity& getEntityFromEID(std::uint64_t);
private:

    const ComponentRegistery& m_componentRegistery;
    std::unordered_map<std::string, Scene> m_scenes;

    Scene* m_current_scene;
    const std::string* m_current_scene_name;

    std::string m_loadingScene;

    const std::function<void(const Code c)> Log;
    const std::function<void(std::string_view str)> LogStr;

    std::vector<std::unique_ptr<Entity>> m_fallbackEntities;
};

}