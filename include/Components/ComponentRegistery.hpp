#pragma once

#include "Entity.hpp"
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp>

namespace cpuEng
{

class ComponentRegistery
{
public:
    using FactoryFunc = std::function<void(Entity&, const nlohmann::json&)>;

    void Register(const std::string& name, FactoryFunc factory);

    void AddComponent(Entity& e, const std::string& component_name, const nlohmann::json& json_data) const;

private:

    std::unordered_map<std::string, FactoryFunc> m_factories;

};

}