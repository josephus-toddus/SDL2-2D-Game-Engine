#pragma once


namespace cpuEng
{
    class Entity; //forward declaration to prevent problems with circular includes

    class Component
    {
    public:
        virtual ~Component() = default;
    protected:
        Entity* p_owner;
    };
};