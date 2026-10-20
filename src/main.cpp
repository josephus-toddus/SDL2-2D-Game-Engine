
#include "Game.hpp"

int main() 
{
    cpuEng::Game g(800, 600, 60.0f, true);

    g.MakeScene("Scene 1", "assets/Scenes/scene_1.json");
    g.SetCurrentScene("Scene 1");



    g.Loop();

    return 0;
}