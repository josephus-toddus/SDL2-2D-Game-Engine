#include "ComponentPresets.hpp"

void cpuEng::LoadRegisteryPresets(ComponentRegistery& componentRegistery, TextureManager& textureManager, SceneManager& sceneManager) 
{
    componentRegistery.Register("Position", [](Entity& e, const nlohmann::json& data){
        if (!data.contains("x") || !data["x"].is_number()) {
            throw std::runtime_error("Missing or Invalid x in Position Component JSON data.");
        }
        if (!data.contains("y") || !data["y"].is_number()) {
            throw std::runtime_error("Missing or Invalid y in Position Component JSON data.");
        }

        e.AddComponent<Position_Component>(
            Position{
                data["x"].get<float>(),
                data["y"].get<float>()
            }
        );
    });

    componentRegistery.Register("Collision", [](Entity& e, const nlohmann::json& data){
        if (!data.contains("width") || !data["width"].is_number_integer()) {
            throw std::runtime_error("Missing or Invalid width in Collision Component JSON data.");
        }
        if (!data.contains("height") || !data["height"].is_number_integer()) {
            throw std::runtime_error("Missing or Invalid height in Collision Component JSON data.");
        }

        e.AddComponent<Collision_Component>(
            Dimensions{
                data["width"].get<int>(),
                data["height"].get<int>()
            }
        );
    });

    componentRegistery.Register("Velocity", [](Entity& e, const nlohmann::json& data){
        if (!data.contains("x_speed") || !data["x_speed"].is_number()) {
            throw std::runtime_error("Missing or Invalid x_speed in Velocity Component JSON data.");
        }
        if (!data.contains("y_speed") || !data["y_speed"].is_number()) {
            throw std::runtime_error("Missing or Invalid y_speed in Velocity Component JSON data.");
        }
        if (!data.contains("x_acc") || !data["x_acc"].is_number()) {
            throw std::runtime_error("Missing or Invalid x_acc in Velocity Component JSON data.");
        }
        if (!data.contains("y_acc") || !data["y_acc"].is_number()) {
            throw std::runtime_error("Missing or Invalid y_acc in Velocity Component JSON data.");
        }

        e.AddComponent<Velocity_Component>(
            Vector2D{
                data["x_speed"].get<float>(),
                data["y_speed"].get<float>()
            },
            Vector2D{
                data["x_acc"].get<float>(),
                data["y_acc"].get<float>()
            }
        );
    });

    componentRegistery.Register("Horizontal_Gravity", [](Entity& e, const nlohmann::json& data){
        if (!data.contains("x_gravityAcceleration") || !data["x_gravityAcceleration"].is_number_integer()) {
            throw std::runtime_error("Missing or Invalid x_gravityAcceleration in Horizontal_Gravity Component JSON data.");
        }

        e.AddComponent<Horizontal_Gravity_Component>(
            data["x_gravityAcceleration"].get<int>()
        );
    });

    componentRegistery.Register("Vertical_Gravity", [](Entity& e, const nlohmann::json& data){
        if (!data.contains("y_gravityAcceleration") || !data["y_gravityAcceleration"].is_number_integer()) {
            throw std::runtime_error("Missing or Invalid y_gravityAcceleration in Vertical_Gravity Component JSON data.");
        }
        e.AddComponent<Vertical_Gravity_Component>(
            data["y_gravityAcceleration"].get<int>()
        );
    });

    componentRegistery.Register("Texture", [&textureManager, &sceneManager](Entity& e, const nlohmann::json& data){
        if (!data.contains("path") || !data["path"].is_string()) {
            throw std::runtime_error("Missing or Invalid path in Texture Component JSON data.");
        }

        const std::string& name = data["path"].get<std::string>();
        textureManager.AddTexture(name, sceneManager.getCurrentSceneName());
        e.AddComponent<Texture_Component>(
            textureManager.getTexture(name)
        );
    });

    componentRegistery.Register("Animation", [&textureManager, &sceneManager](Entity& e, const nlohmann::json& data){
        if (!data.contains("paths") || !data["paths"].is_array()) {
            throw std::runtime_error("Missing or Invalid paths array in Animation Component JSON data.");
        }
        if (!data.contains("fps") || !data["fps"].is_number_unsigned() || !data["fps"].is_number_integer()) {
            throw std::runtime_error("Missing or Invalid fps in Animation Component JSON data.");
        }
        
        const std::vector<std::string>& names = data["paths"].get<std::vector<std::string>>();

        textureManager.AddAnimation(names, data["fps"].get<int>(), sceneManager.getCurrentSceneName());

        e.AddComponent<Animation_Component>(
            textureManager.getAnimation(names[0])
        );
    });

    componentRegistery.Register("Texture_Set", [&textureManager, &sceneManager](Entity& e, const nlohmann::json& data){
        if (!data.contains("sets") || !data["sets"].is_array()) {
            throw std::runtime_error("Missing or Invalid sets array in Texture_Set Component JSON data.");
        }

        auto sets = data["sets"];

        int successfulSets = 0;
        std::unordered_map<std::string, const Texture*> setOfTextures;

        for (int i = 0; i < sets.size(); ++i) {
            if (!sets[i].contains("name") || !sets[i]["name"].is_string()) {
                continue;
            }
            if (!sets[i].contains("path") || !sets[i]["path"].is_string()) {
                continue;
            }

            const std::string& name = sets[i]["name"].get<std::string>();
            const std::string& path = sets[i]["path"].get<std::string>();

            if (setOfTextures.contains(name)) {
                continue;
            }

            textureManager.AddTexture(path, sceneManager.getCurrentSceneName());

            setOfTextures[name] = &textureManager.getTexture(path);

            ++successfulSets;
        }

        if (successfulSets == 0) {
            throw std::runtime_error("All Textures failed to load, aborted.");
        }

        e.AddComponent<Texture_Set_Component>(setOfTextures);
    });

    componentRegistery.Register("Animation_Set", [&textureManager, &sceneManager](Entity& e, const nlohmann::json& data){
        if (!data.contains("sets") || !data["sets"].is_array()) {
            throw std::runtime_error("Missing or Invalid sets array in Animation_Set Component JSON data.");
        }

        auto sets = data["sets"];

        int successfulSets = 0;
        std::unordered_map<std::string, const Animation*> setOfAnimations;

        for (int i = 0; i < sets.size(); ++i) {
            if (!sets[i].contains("name") || !sets[i]["name"].is_string()) {
                continue;
            }
            if (!sets[i].contains("paths") || !sets[i]["path"].is_array()) {
                continue;
            }
            if (!sets[i].contains("fps") || !sets[i]["fps"].is_number_integer() || !sets[i]["fps"].is_number_unsigned()) {
                continue;
            }
            if (sets[i]["path"].empty() || !sets[i]["path"][0].is_string()) {
                continue;
            }

            const std::string& name = sets[i]["name"].get<std::string>();
            const std::vector<std::string>& paths = sets[i]["path"].get<std::vector<std::string>>();
            const int fps = sets[i]["fps"].get<int>();

            if (setOfAnimations.contains(name)) {
                continue;
            }

            textureManager.AddAnimation(paths, fps, sceneManager.getCurrentSceneName());

            setOfAnimations[name] = &textureManager.getAnimation(paths[0]);

            ++successfulSets;
        }

        if (successfulSets == 0) {
            throw std::runtime_error("All Textures failed to load, aborted.");
        }

        e.AddComponent<Animation_Set_Component>(setOfAnimations);
    });

    //Do other variants next. Done I believe tbh.
}