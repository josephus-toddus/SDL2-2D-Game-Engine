#include "ComponentRegistery.hpp"
#include "TextureManager.hpp"
#include "Entity.hpp"
#include "Codes.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <fstream>
#include <functional>


#pragma once
namespace cpuEng
{


class Scene 
{
public:
    Scene();
    Scene(const std::string& filepath, 
          const ComponentRegistery& componentRegistery, 
          const std::function<void(const Code c)>& Log,
          const std::function<void(std::string_view)>& LogStr
    );
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    bool failedRead();


private:
    bool m_failedRead;
    std::vector<std::unique_ptr<Entity>> m_entities;

    const std::function<void(const Code c)>& Log;
    const std::function<void(std::string_view str)>& LogStr;
};


}