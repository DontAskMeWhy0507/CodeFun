#include "Input.h"
#include "Engine.h"
#include "Timer.h"
Input* Input::s_Instance = nullptr;

Input::Input(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    m_KeyDownTime = 0;
}

void Input::Listen(){
    SDL_Event event;
    if (m_KeyStates[SDL_SCANCODE_SPACE])
                    m_KeyDownTime += 0.5;

    if(m_KeyDownTime >30) m_KeyDownTime = 30;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: Engine::GetInstance()->Quit(); break;
            case SDL_KEYDOWN:
                 KeyDown();
                 break;
            case SDL_KEYUP:
                KeyUp();
                 if (!m_KeyStates[SDL_SCANCODE_SPACE])   m_KeyDownTime = 0; // Reset thời gian khi phím được thả ra
                break;
        }
    }



}


bool Input::GetKeyDown(SDL_Scancode key){
    if(m_KeyStates[key] == 1) {
        m_LastKeyDown = key;
        return true;
    }
    return false;
}

//m_keyStates là mảng chứa trạng thái của các phím. Ví dụ phím d được ấn thì m_keyStates[SDL_SCANCODE_D] = 1. Còn không thì = 0
void Input::KeyUp(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}
