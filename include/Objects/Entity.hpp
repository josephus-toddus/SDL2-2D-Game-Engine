#pragma once

#include <Texture.hpp>
#include <memory>
#include "Component.hpp"
#include <concepts>
#include <algorithm>

namespace cpuEng
{
    class Entity
    {
    private:

        std::uint64_t m_eid;
        std::vector<std::unique_ptr<Component>> m_components;
    
    public:
        
        Entity(std::uint64_t eid);
        
        // adds a component to the entity
        template <typename T, typename... Targs>
        void AddComponent(Targs&&... args)
        {
            if (GetComponent<T>()) { // Makes sure that it doesn't already exist
                return;
            }

            m_components.push_back(std::make_unique<T>(std::forward<Targs>(args)... )); 
        }

        // returns nullptr if absent from m_components, if present a raw pointer to the component
        template <typename T>
        T* GetComponent() const
        {
            for (const auto& component : m_components) {
                if (T* result = dynamic_cast<T*>(component.get())) {
                    return result;
                }
            }
            return nullptr;
        }
    };
}