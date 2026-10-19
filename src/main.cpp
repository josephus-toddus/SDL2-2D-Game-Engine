
#include "Game.hpp"

#include <print>
#include <climits>
#include <thread>
#include <format>
#include <utility>

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
    e.AddComponent<cpuEng::Position_Component>(cpuEng::Position({0.0f, 0.0f}));
    const auto& poscomp = e.GetComponent<cpuEng::Position_Component>();

    cpuEng::Window window(800, 600);
    cpuEng::InputManager input;
    cpuEng::EventManager events(window, input);

    std::vector<cpuEng::Entity> entities;
    entities.push_back(std::move(e));

    cpuEng::LogicManager logic(input, events, &entities);

    logic.AddLogic(42ULL, [](cpuEng::Entity& e, cpuEng::UpdateContext& contx) {
        const auto& comp = e.GetComponent<cpuEng::Position_Component>();
        if (comp) {
            if (contx.input.IsKeyDown(cpuEng::KeyCode::Space)) {
                comp->pos.y++;
                return;
            }
            comp->pos.y--;
        }
    });


    auto lastTime = std::chrono::steady_clock::now();
    window.setBackGround(0xFFFFFFFF);

    while (true) {

        std::cout << poscomp->pos.x << ", "
                  << poscomp->pos.y << '\n';


        input.Update();
        logic.UpdateLogic(16);

        window.upDateWindow();

        if (events.CheckEvents() == -1) {
            SDL_Quit();
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }


    return 0;
}