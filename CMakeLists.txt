cmake_minimum_required(VERSION 3.22)
project(SDL2_Game_Engine C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

if (APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
        src/main.cpp
        src/Window.cpp
        src/close.cpp
        src/init.cpp
        src/Texture.cpp
        src/Sprite.cpp
    )
    set_source_files_properties(assets PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_sources(${PROJECT_NAME} PRIVATE assets)

elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32
        src/main.cpp
        src/Window.cpp
        src/close.cpp
        src/init.cpp
        src/Texture.cpp
        src/Sprite.cpp
    )
else()
    add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/close.cpp
        src/init.cpp
        src/Texture.cpp
        src/Sprite.cpp
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")