
#include "Game.hpp"

int main() 
{
    cpuEng::Game g(800, 600, 60.0f, true);

    g.MakeScene("Scene 1", "assets/Scenes/scene_1.json");
    g.SetCurrentScene("Scene 1");

    g.InitCamera("Camera 1");

    g.AddLogicToEntity(0, [](cpuEng::Entity& entity, cpuEng::UpdateContext context){
        auto pos = entity.GetComponent<cpuEng::Position_Component>();
        if (!pos) {
            return;
        }

        if (context.input.IsKeyDown(cpuEng::KeyCode::W)) {
            pos->pos.y -= 10;
        }
        else if (context.input.IsKeyDown(cpuEng::KeyCode::A)) {
            pos->pos.x -= 10;
        }
        else if (context.input.IsKeyDown(cpuEng::KeyCode::S)) {
            pos->pos.y += 10;
        }
        else if (context.input.IsKeyDown(cpuEng::KeyCode::D)) {
            pos->pos.x += 10;
        }

    });



    g.Loop();

    return 0;
}