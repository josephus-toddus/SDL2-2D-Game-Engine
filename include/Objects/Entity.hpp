#include <Texture.hpp>
#include <memory>
#include <Component.hpp>
#include <concepts>
#include <algorithm>

#pragma once

namespace cpuEng
{
    class Entity
    {
    public:
        
        Entity(std::uint64_t eid);
        
        //adds a component to the enity
        template <std::derived_from<Component> T, typename... Targs>
        void AddComponent(Targs&&... args)
        {
            if (GetComponent<T>()) // Makes sure that it doesn't already exist
            {
                return;
            }

            m_components.push_back(std::make_unique<T>(std::forward<Targs>(args)... )); 
        }

        // returns nullptr absent from m_components, if present a raw pointer to the component
        template <std::derived_from<Component> T>
        T* GetComponent()
        {
            for (const auto& component : m_components)
            {
                if (T* result = dynamic_cast<T*>(component.get()))
                {
                    return result;
                }
            }
            return nullptr;
        }

    private:

        std::uint64_t m_eid;
        std::vector<std::unique_ptr<Component>> m_components;
    };
};