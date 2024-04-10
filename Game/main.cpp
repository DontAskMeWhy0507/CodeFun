#include <iostream>
#include "SDL.h"
#include "Engine.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Timer.h"

using namespace std;

int main(int argc, char* argv[]) {
    Engine::GetInstance()->Init(); // Initialize game engine

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // Load music
    Mix_Music* music = Mix_LoadMUS("assets/sounds/MainSound.mp3");
    if (!music) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/Font/test.ttf", 24); // Change "YourFont.ttf" to your font file path
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // Play the music
    Mix_PlayMusic(music, -1); // -1 loops the music indefinitely

    //Hàm while để ảnh được render liên tục.
    while(Engine::GetInstance()-> IsRunning()){     //KIEM TRA XEM GAME CO DANG CHAY KHONG
        Engine ::GetInstance()->Events();           //Sự kiện từ người dùng (ví dụ như ấn X để tắt game)
        Engine ::GetInstance()->Update();              //
        Engine ::GetInstance()->Render();               //Render ảnh
        Timer ::GetInstance()->Tick();                  //Khởi tạo lại DeltaTime liên tục

        // Render text using SDL_ttf
        SDL_Color textColor = {255, 255, 255}; // White color
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello adfasdfasdfasdfa sdfasd asdfa sdfas d fasdfasdfasdf asdf sadfSDL_ttf!", textColor);
        if (!textSurface) {
            printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return -1;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), textSurface);
        if (!textTexture) {
            printf("Failed to create text texture! SDL Error: %s\n", SDL_GetError());
            return -1;
        }

        SDL_Rect textRect = {20, 10, textSurface->w, textSurface->h}; // Position to render the text
        SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    // Clean up resources
    Mix_FreeMusic(music);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    Engine::GetInstance()->Clean();         //XOA DI SAU KHI CHOI XONG
    return 0;
}
