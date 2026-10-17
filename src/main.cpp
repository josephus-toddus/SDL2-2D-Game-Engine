
#include "Game.hpp"

#include <iostream>

class TestComponent : public cpuEng::Component
{
    public:
        TestComponent(int a) : a{a}{}
        int a;
};

int main() 
{
    int a;
    std::cout<<"Hello, World!\n\nThis, suprisingly, compiled and ran fine!";
    std::cin>>a;

    cpuEng::Entity e(42ULL);
    e.AddComponent<TestComponent>(42);
    const auto& comp = e.GetComponent<TestComponent>();
    std::cout << "Did it work??? " << comp->a;
    return 0;
}