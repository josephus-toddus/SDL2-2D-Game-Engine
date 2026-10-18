#include "ComponentRegistery.hpp"
#include "TextureManager.hpp"
#include "Entity.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>


#pragma once
namespace cpuEng
{


class Scene 
{
public:
    Scene();
    Scene(const std::string& filepath, const ComponentRegistery& componentRegistery);
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    bool failedRead();


private:
    bool m_failedRead;
    std::vector<std::unique_ptr<Entity>> m_entities;
};


}