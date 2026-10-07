#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include "Position.hpp"

namespace cpuEng
{


enum class KeyCode
{
    // Letters
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    // Main keyboard
    Enter,
    Space,
    Backspace,
    Left_Shift,
    Right_Shift,
    CapsLock,
    Tab,
    Left_Ctrl,
    Right_Ctrl,
    Left_Alt,
    Right_Alt,
    Esc,
    Delete,

    // Number row
    _1, _2, _3, _4, _5,
    _6, _7, _8, _9, _0,

    // Numpad
    NUMPAD_1,
    NUMPAD_2,
    NUMPAD_3,
    NUMPAD_4,
    NUMPAD_5,
    NUMPAD_6,
    NUMPAD_7,
    NUMPAD_8,
    NUMPAD_9,
    NUMPAD_0,
    NUMPAD_Dot,
    NUMPAD_Add,
    NUMPAD_Subtract,
    NUMPAD_Multiply,
    NUMPAD_Divide,
    NUMPAD_Enter,
    NumLock,

    // Navigation
    LEFT,
    UP,
    DOWN,
    RIGHT,
    Home,
    End,
    PageUp,
    PageDown,
    Insert,

    // Function keys
    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,

    // Punctuation / symbol keys
    OpenSquareBrackets,
    CloseSquareBrackets,
    SemiColon,
    Apostrophe,
    Comma,
    Dot,
    ForwardSlash,
    Backslash,
    Minus,
    Equals,
    Grave,

    // Other
    PrintScreen,
    ScrollLock,
    Pause,

    //Mouse buttons
    Mouse_Left,
    Mouse_Right,
    Mouse_Middle,

    Count
};

enum class KeyStates
{
    Up,
    Down,
    Pressed,
    Released
};

class InputManager
{
public:

    InputManager();

    void Update();

    bool IsKeyPressed(KeyCode key);
    bool IsKeyDown(KeyCode key);
    bool IsKeyReleased(KeyCode key);
    bool IsKeyUp(KeyCode key);

    void Remap(KeyCode key, SDL_Scancode scan_code);
    void Remap(KeyCode key, std::uint8_t button);

    void Remap(KeyCode key, KeyCode key2);

    int GetMouseX() const;
    int GetMouseY() const;

    static bool IsMouseButton(KeyCode key);


private:

    std::unordered_map <std::uint8_t, KeyCode> m_ButtonStateToKey;

    std::unordered_map <KeyCode, SDL_Scancode> m_KeyToScan;
    std::unordered_map <KeyCode, std::uint8_t> m_KeyToButtonState;

    std::array<KeyStates, static_cast<size_t>(KeyCode::Count)> m_keyboard; 
    // IF YOU ADD MORE KEYS CHANGE THIS yep I did it was 84 before. and then it was 99 and then it was 102
    // And now chatgpt suggested something really smart (it was 104 before)

    int m_MouseX;
    int m_MouseY;

    friend class EventManager;
    
};

}