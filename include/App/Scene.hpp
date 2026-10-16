#include "TextureManager.hpp"
#include "Entity.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <json.hpp>


#pragma once
namespace cpuEng
{


class Scene 
{
public:

    Scene(const std::string& name, const std::string& filepath);
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    const std::string& getName() const;


private:
    const std::string m_name;
    std::vector<std::unique_ptr<Entity>> m_entities;
};


}