#include "ComponentRegistery.hpp"

void cpuEng::ComponentRegistery::Register(const std::string& name, FactoryFunc factory)
{
    m_factories.insert_or_assign(name, std::move(factory));
}

void cpuEng::ComponentRegistery::AddComponent(Entity& e, const std::string& component_name, const nlohmann::json& json_data) const
{
    const auto it = m_factories.find(component_name);

    if (it == m_factories.end()) {
        throw std::runtime_error("Unknown Component: " + component_name);
    }

    it->second(e, json_data);
}