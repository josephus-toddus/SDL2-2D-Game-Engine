#include "InputManager.hpp"

cpuEng::InputManager::InputManager() :
    m_MouseX(0),
    m_MouseY(0)
{
    m_ScanToKey =
    {
        // Letters
        {SDL_SCANCODE_A, KeyCode::A},
        {SDL_SCANCODE_B, KeyCode::B},
        {SDL_SCANCODE_C, KeyCode::C},
        {SDL_SCANCODE_D, KeyCode::D},
        {SDL_SCANCODE_E, KeyCode::E},
        {SDL_SCANCODE_F, KeyCode::F},
        {SDL_SCANCODE_G, KeyCode::G},
        {SDL_SCANCODE_H, KeyCode::H},
        {SDL_SCANCODE_I, KeyCode::I},
        {SDL_SCANCODE_J, KeyCode::J},
        {SDL_SCANCODE_K, KeyCode::K},
        {SDL_SCANCODE_L, KeyCode::L},
        {SDL_SCANCODE_M, KeyCode::M},
        {SDL_SCANCODE_N, KeyCode::N},
        {SDL_SCANCODE_O, KeyCode::O},
        {SDL_SCANCODE_P, KeyCode::P},
        {SDL_SCANCODE_Q, KeyCode::Q},
        {SDL_SCANCODE_R, KeyCode::R},
        {SDL_SCANCODE_S, KeyCode::S},
        {SDL_SCANCODE_T, KeyCode::T},
        {SDL_SCANCODE_U, KeyCode::U},
        {SDL_SCANCODE_V, KeyCode::V},
        {SDL_SCANCODE_W, KeyCode::W},
        {SDL_SCANCODE_X, KeyCode::X},
        {SDL_SCANCODE_Y, KeyCode::Y},
        {SDL_SCANCODE_Z, KeyCode::Z},

        // Main keyboard
        {SDL_SCANCODE_RETURN,    KeyCode::Enter},
        {SDL_SCANCODE_SPACE,     KeyCode::Space},
        {SDL_SCANCODE_BACKSPACE, KeyCode::Backspace},
        {SDL_SCANCODE_LSHIFT,    KeyCode::Left_Shift},
        {SDL_SCANCODE_RSHIFT,    KeyCode::Right_Shift},
        {SDL_SCANCODE_CAPSLOCK,  KeyCode::CapsLock},
        {SDL_SCANCODE_TAB,       KeyCode::Tab},
        {SDL_SCANCODE_LCTRL,     KeyCode::Left_Ctrl},
        {SDL_SCANCODE_RCTRL,     KeyCode::Right_Ctrl},
        {SDL_SCANCODE_LALT,      KeyCode::Left_Alt},
        {SDL_SCANCODE_RALT,      KeyCode::Right_Alt},
        {SDL_SCANCODE_ESCAPE,    KeyCode::Esc},
        {SDL_SCANCODE_DELETE,    KeyCode::Delete},

        // Number row
        {SDL_SCANCODE_1, KeyCode::_1},
        {SDL_SCANCODE_2, KeyCode::_2},
        {SDL_SCANCODE_3, KeyCode::_3},
        {SDL_SCANCODE_4, KeyCode::_4},
        {SDL_SCANCODE_5, KeyCode::_5},
        {SDL_SCANCODE_6, KeyCode::_6},
        {SDL_SCANCODE_7, KeyCode::_7},
        {SDL_SCANCODE_8, KeyCode::_8},
        {SDL_SCANCODE_9, KeyCode::_9},
        {SDL_SCANCODE_0, KeyCode::_0},

        // Numpad
        {SDL_SCANCODE_KP_1,         KeyCode::NUMPAD_1},
        {SDL_SCANCODE_KP_2,         KeyCode::NUMPAD_2},
        {SDL_SCANCODE_KP_3,         KeyCode::NUMPAD_3},
        {SDL_SCANCODE_KP_4,         KeyCode::NUMPAD_4},
        {SDL_SCANCODE_KP_5,         KeyCode::NUMPAD_5},
        {SDL_SCANCODE_KP_6,         KeyCode::NUMPAD_6},
        {SDL_SCANCODE_KP_7,         KeyCode::NUMPAD_7},
        {SDL_SCANCODE_KP_8,         KeyCode::NUMPAD_8},
        {SDL_SCANCODE_KP_9,         KeyCode::NUMPAD_9},
        {SDL_SCANCODE_KP_0,         KeyCode::NUMPAD_0},
        {SDL_SCANCODE_KP_PERIOD,    KeyCode::NUMPAD_Dot},
        {SDL_SCANCODE_KP_PLUS,      KeyCode::NUMPAD_Add},
        {SDL_SCANCODE_KP_MINUS,     KeyCode::NUMPAD_Subtract},
        {SDL_SCANCODE_KP_MULTIPLY,  KeyCode::NUMPAD_Multiply},
        {SDL_SCANCODE_KP_DIVIDE,    KeyCode::NUMPAD_Divide},
        {SDL_SCANCODE_KP_ENTER,     KeyCode::NUMPAD_Enter},
        {SDL_SCANCODE_NUMLOCKCLEAR, KeyCode::NumLock},

        // Navigation
        {SDL_SCANCODE_LEFT,     KeyCode::LEFT},
        {SDL_SCANCODE_UP,       KeyCode::UP},
        {SDL_SCANCODE_DOWN,     KeyCode::DOWN},
        {SDL_SCANCODE_RIGHT,    KeyCode::RIGHT},
        {SDL_SCANCODE_HOME,     KeyCode::Home},
        {SDL_SCANCODE_END,      KeyCode::End},
        {SDL_SCANCODE_PAGEUP,   KeyCode::PageUp},
        {SDL_SCANCODE_PAGEDOWN, KeyCode::PageDown},
        {SDL_SCANCODE_INSERT,   KeyCode::Insert},

        // Function keys
        {SDL_SCANCODE_F1,  KeyCode::F1},
        {SDL_SCANCODE_F2,  KeyCode::F2},
        {SDL_SCANCODE_F3,  KeyCode::F3},
        {SDL_SCANCODE_F4,  KeyCode::F4},
        {SDL_SCANCODE_F5,  KeyCode::F5},
        {SDL_SCANCODE_F6,  KeyCode::F6},
        {SDL_SCANCODE_F7,  KeyCode::F7},
        {SDL_SCANCODE_F8,  KeyCode::F8},
        {SDL_SCANCODE_F9,  KeyCode::F9},
        {SDL_SCANCODE_F10, KeyCode::F10},
        {SDL_SCANCODE_F11, KeyCode::F11},
        {SDL_SCANCODE_F12, KeyCode::F12},

        // Punctuation / symbol keys
        {SDL_SCANCODE_LEFTBRACKET,  KeyCode::OpenSquareBrackets},
        {SDL_SCANCODE_RIGHTBRACKET, KeyCode::CloseSquareBrackets},
        {SDL_SCANCODE_SEMICOLON,    KeyCode::SemiColon},
        {SDL_SCANCODE_APOSTROPHE,   KeyCode::Apostrophe},
        {SDL_SCANCODE_COMMA,        KeyCode::Comma},
        {SDL_SCANCODE_PERIOD,       KeyCode::Dot},
        {SDL_SCANCODE_SLASH,        KeyCode::ForwardSlash},
        {SDL_SCANCODE_BACKSLASH,    KeyCode::Backslash},
        {SDL_SCANCODE_MINUS,        KeyCode::Minus},
        {SDL_SCANCODE_EQUALS,       KeyCode::Equals},
        {SDL_SCANCODE_GRAVE,        KeyCode::Grave},

        // Other
        {SDL_SCANCODE_PRINTSCREEN, KeyCode::PrintScreen},
        {SDL_SCANCODE_SCROLLLOCK,  KeyCode::ScrollLock},
        {SDL_SCANCODE_PAUSE,       KeyCode::Pause},
    };

    m_ButtonStateToKey = 
    {
        {SDL_BUTTON_LEFT, KeyCode::Mouse_Left},
        {SDL_BUTTON_RIGHT, KeyCode::Mouse_Right},
        {SDL_BUTTON_MIDDLE, KeyCode::Mouse_Middle}
    };

    m_KeyToScan =
    {
        // Letters
        {KeyCode::A, SDL_SCANCODE_A},
        {KeyCode::B, SDL_SCANCODE_B},
        {KeyCode::C, SDL_SCANCODE_C},
        {KeyCode::D, SDL_SCANCODE_D},
        {KeyCode::E, SDL_SCANCODE_E},
        {KeyCode::F, SDL_SCANCODE_F},
        {KeyCode::G, SDL_SCANCODE_G},
        {KeyCode::H, SDL_SCANCODE_H},
        {KeyCode::I, SDL_SCANCODE_I},
        {KeyCode::J, SDL_SCANCODE_J},
        {KeyCode::K, SDL_SCANCODE_K},
        {KeyCode::L, SDL_SCANCODE_L},
        {KeyCode::M, SDL_SCANCODE_M},
        {KeyCode::N, SDL_SCANCODE_N},
        {KeyCode::O, SDL_SCANCODE_O},
        {KeyCode::P, SDL_SCANCODE_P},
        {KeyCode::Q, SDL_SCANCODE_Q},
        {KeyCode::R, SDL_SCANCODE_R},
        {KeyCode::S, SDL_SCANCODE_S},
        {KeyCode::T, SDL_SCANCODE_T},
        {KeyCode::U, SDL_SCANCODE_U},
        {KeyCode::V, SDL_SCANCODE_V},
        {KeyCode::W, SDL_SCANCODE_W},
        {KeyCode::X, SDL_SCANCODE_X},
        {KeyCode::Y, SDL_SCANCODE_Y},
        {KeyCode::Z, SDL_SCANCODE_Z},

        // Main keyboard
        {KeyCode::Enter,       SDL_SCANCODE_RETURN},
        {KeyCode::Space,       SDL_SCANCODE_SPACE},
        {KeyCode::Backspace,   SDL_SCANCODE_BACKSPACE},
        {KeyCode::Left_Shift,  SDL_SCANCODE_LSHIFT},
        {KeyCode::Right_Shift, SDL_SCANCODE_RSHIFT},
        {KeyCode::CapsLock,    SDL_SCANCODE_CAPSLOCK},
        {KeyCode::Tab,         SDL_SCANCODE_TAB},
        {KeyCode::Left_Ctrl,   SDL_SCANCODE_LCTRL},
        {KeyCode::Right_Ctrl,  SDL_SCANCODE_RCTRL},
        {KeyCode::Left_Alt,    SDL_SCANCODE_LALT},
        {KeyCode::Right_Alt,   SDL_SCANCODE_RALT},
        {KeyCode::Esc,         SDL_SCANCODE_ESCAPE},
        {KeyCode::Delete,      SDL_SCANCODE_DELETE},

        // Number row
        {KeyCode::_1, SDL_SCANCODE_1},
        {KeyCode::_2, SDL_SCANCODE_2},
        {KeyCode::_3, SDL_SCANCODE_3},
        {KeyCode::_4, SDL_SCANCODE_4},
        {KeyCode::_5, SDL_SCANCODE_5},
        {KeyCode::_6, SDL_SCANCODE_6},
        {KeyCode::_7, SDL_SCANCODE_7},
        {KeyCode::_8, SDL_SCANCODE_8},
        {KeyCode::_9, SDL_SCANCODE_9},
        {KeyCode::_0, SDL_SCANCODE_0},

        // Numpad
        {KeyCode::NUMPAD_1,        SDL_SCANCODE_KP_1},
        {KeyCode::NUMPAD_2,        SDL_SCANCODE_KP_2},
        {KeyCode::NUMPAD_3,        SDL_SCANCODE_KP_3},
        {KeyCode::NUMPAD_4,        SDL_SCANCODE_KP_4},
        {KeyCode::NUMPAD_5,        SDL_SCANCODE_KP_5},
        {KeyCode::NUMPAD_6,        SDL_SCANCODE_KP_6},
        {KeyCode::NUMPAD_7,        SDL_SCANCODE_KP_7},
        {KeyCode::NUMPAD_8,        SDL_SCANCODE_KP_8},
        {KeyCode::NUMPAD_9,        SDL_SCANCODE_KP_9},
        {KeyCode::NUMPAD_0,        SDL_SCANCODE_KP_0},
        {KeyCode::NUMPAD_Dot,      SDL_SCANCODE_KP_PERIOD},
        {KeyCode::NUMPAD_Add,      SDL_SCANCODE_KP_PLUS},
        {KeyCode::NUMPAD_Subtract, SDL_SCANCODE_KP_MINUS},
        {KeyCode::NUMPAD_Multiply, SDL_SCANCODE_KP_MULTIPLY},
        {KeyCode::NUMPAD_Divide,   SDL_SCANCODE_KP_DIVIDE},
        {KeyCode::NUMPAD_Enter,    SDL_SCANCODE_KP_ENTER},
        {KeyCode::NumLock,         SDL_SCANCODE_NUMLOCKCLEAR},

        // Navigation
        {KeyCode::LEFT,    SDL_SCANCODE_LEFT},
        {KeyCode::UP,      SDL_SCANCODE_UP},
        {KeyCode::DOWN,    SDL_SCANCODE_DOWN},
        {KeyCode::RIGHT,   SDL_SCANCODE_RIGHT},
        {KeyCode::Home,    SDL_SCANCODE_HOME},
        {KeyCode::End,     SDL_SCANCODE_END},
        {KeyCode::PageUp,  SDL_SCANCODE_PAGEUP},
        {KeyCode::PageDown,SDL_SCANCODE_PAGEDOWN},
        {KeyCode::Insert,  SDL_SCANCODE_INSERT},

        // Function keys
        {KeyCode::F1,  SDL_SCANCODE_F1},
        {KeyCode::F2,  SDL_SCANCODE_F2},
        {KeyCode::F3,  SDL_SCANCODE_F3},
        {KeyCode::F4,  SDL_SCANCODE_F4},
        {KeyCode::F5,  SDL_SCANCODE_F5},
        {KeyCode::F6,  SDL_SCANCODE_F6},
        {KeyCode::F7,  SDL_SCANCODE_F7},
        {KeyCode::F8,  SDL_SCANCODE_F8},
        {KeyCode::F9,  SDL_SCANCODE_F9},
        {KeyCode::F10, SDL_SCANCODE_F10},
        {KeyCode::F11, SDL_SCANCODE_F11},
        {KeyCode::F12, SDL_SCANCODE_F12},

        // Punctuation / symbol keys
        {KeyCode::OpenSquareBrackets,  SDL_SCANCODE_LEFTBRACKET},
        {KeyCode::CloseSquareBrackets, SDL_SCANCODE_RIGHTBRACKET},
        {KeyCode::SemiColon,           SDL_SCANCODE_SEMICOLON},
        {KeyCode::Apostrophe,          SDL_SCANCODE_APOSTROPHE},
        {KeyCode::Comma,               SDL_SCANCODE_COMMA},
        {KeyCode::Dot,                 SDL_SCANCODE_PERIOD},
        {KeyCode::ForwardSlash,        SDL_SCANCODE_SLASH},
        {KeyCode::Backslash,           SDL_SCANCODE_BACKSLASH},
        {KeyCode::Minus,               SDL_SCANCODE_MINUS},
        {KeyCode::Equals,              SDL_SCANCODE_EQUALS},
        {KeyCode::Grave,               SDL_SCANCODE_GRAVE},

        // Other
        {KeyCode::PrintScreen, SDL_SCANCODE_PRINTSCREEN},
        {KeyCode::ScrollLock,  SDL_SCANCODE_SCROLLLOCK},
        {KeyCode::Pause,       SDL_SCANCODE_PAUSE},
    };

    m_KeyToButtonState =
    {
        {KeyCode::Mouse_Left,   SDL_BUTTON_LEFT},
        {KeyCode::Mouse_Right,  SDL_BUTTON_RIGHT},
        {KeyCode::Mouse_Middle, SDL_BUTTON_MIDDLE}
    };

    UpdateKeyboardState();
}

void cpuEng::InputManager::UpdateKeyboardState() {
    int numKeys;
    const std::uint8_t* keys = SDL_GetKeyboardState(&numKeys);

    for (const auto& [keyCode, scanCode] : m_KeyToScan) {
        int sdlIndex = static_cast<int>(scanCode);
        int targetIndex = static_cast<int>(keyCode);

        int keycode = static_cast<int>(keyCode);
        KeyStates keystate = keyboard.at(keycode);

        keyboard[keycode] =
            (keys[sdlIndex]) ?
                (keystate == KeyStates::Up || keystate == KeyStates::Released)
                ?
                    KeyStates::Pressed
                    :
                    KeyStates::Down
                :
                (keystate == KeyStates::Down || keystate == KeyStates::Pressed) ?
                    KeyStates::Released
                    :
                    KeyStates::Up;
    }

    std::uint32_t mouseState = SDL_GetMouseState(&m_MouseX, &m_MouseY);

    for (std::uint8_t key : {SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT}) {
        int keycode = static_cast<int>(m_ButtonStateToKey.at(key));
        KeyStates keystate = keyboard.at(keycode);

        keyboard[keycode] =
            (mouseState & SDL_BUTTON(key)) ?
                (keystate == KeyStates::Up || keystate == KeyStates::Released)
                ?
                    KeyStates::Pressed
                    :
                    KeyStates::Down
                :
                (keystate == KeyStates::Down || keystate == KeyStates::Pressed) ?
                    KeyStates::Released
                    :
                    KeyStates::Up;
    }
    
}

bool cpuEng::InputManager::IsKeyDown(KeyCode k)
{

}