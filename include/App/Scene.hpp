#include "TextureManager.hpp"
#include "Entity.hpp"
#include <memory>

#pragma once
namespace cpuEng
{


class Scene 
{
public:

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    const std::string& getName() const;


private:
    std::string m_name;

    std::vector<std::unique_ptr<Entity>> m_entities;
};


}