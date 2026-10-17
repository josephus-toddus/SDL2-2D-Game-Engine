#include "TextureManager.hpp"
#include "Entity.hpp"
#include <memory>
#include <nlohmann/json.hpp>


#pragma once
namespace cpuEng
{


class Scene 
{
public:
    Scene();
    Scene(const std::string& filepath);
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    bool failedRead();


private:
    bool m_failedRead;
    std::vector<std::unique_ptr<Entity>> m_entities;
};


}