#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Warrior.h"
#include "SDL.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>
#include "Camera.h"


Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init(){

    if(SDL_Init(SDL_INIT_VIDEO)!=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!= 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr){
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);        //the renderer uses hardware acceleration and the renderer uses hardware acceleration
    if(m_Renderer == nullptr){
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load()){
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    // load texture
    TextureManager::GetInstance()->Load("player", "assets/ide.png");
    TextureManager::GetInstance()->Load("player_run", "assets/Run.png");
    TextureManager::GetInstance()->Load("Background", "assets/Images/bg.png");


    player = new Warrior (new Properties ("player",300,250,200,200));       //(Chỉ số id,x,y,width,height)


    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

void Engine::Update(){

    float dt= Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
    m_LevelMap->Update();
    Camera::GetInstance()->Update(dt);


}

void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 124, 418, 954, 955);             //Màu nền của gamme
    SDL_RenderClear(m_Renderer);                                        //Xóa bỏ nền đen mặc định gây nhiều lỗi

    TextureManager::GetInstance()->Draw("Background",0,0,1004,500);
    m_LevelMap->Render();                                           //Tạo map tiled


    // render texture
    player->Draw();                                                     //vẽ player lên trên game
   SDL_RenderPresent(m_Renderer);                                       //Update m_Renderer lên màn hình sau khi nó được tạo mới
}

void Engine::Events(){
  Input::GetInstance()->Listen();
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();         //Clean của TextủeManager
    MapParser::GetInstance()->Clean();              //Clean của MapParser

    SDL_DestroyRenderer(m_Renderer);                //Clean Renderer
    SDL_DestroyWindow(m_Window);                    //Clean Window
    IMG_Quit();                                       //thoát khỏi sdl img
    SDL_Quit();                                     //thoát khỏi sdl
}

void Engine::Quit(){            //dùng trong function Events của class engine
    m_IsRunning = false;
}
