cmake_minimum_required(VERSION 3.22)
project(SDL2_Game_Engine C CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)


if (APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
        src/main.cpp
        src/Window.cpp
        src/Texture.cpp
        src/Animation.cpp
        src/TextureManager.cpp
        src/Scene.cpp
        src/SceneManager.cpp
        src/Entity.cpp
        src/EventManager.cpp
        src/Camera.cpp
        src/InputManager.cpp
    )
    set_source_files_properties(assets PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_sources(${PROJECT_NAME} PRIVATE assets)

elseif(WIN32)
    add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/Texture.cpp
        src/Animation.cpp
        src/TextureManager.cpp
        src/Scene.cpp
        src/SceneManager.cpp
        src/Entity.cpp
        src/EventManager.cpp
        src/Camera.cpp
        src/InputManager.cpp
    )
else()
    add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/Texture.cpp
        src/Animation.cpp
        src/TextureManager.cpp
        src/Scene.cpp
        src/SceneManager.cpp
        src/Entity.cpp
        src/EventManager.cpp
        src/Camera.cpp
        src/InputManager.cpp
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/App")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/Components")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/General_Def")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/Objects")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/Textures")

target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)