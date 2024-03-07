#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"

#include "Warrior.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init(){

    if(SDL_Init(SDL_INIT_VIDEO)!=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!= 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREN_HEIGHT, 0);
    if(m_Window == nullptr){
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);        //the renderer uses hardware acceleration and the renderer uses hardware acceleration
    if(m_Renderer == nullptr){
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    // load texture
    TextureManager::GetInstance()->Load("player", "assets/ide.png");
    player = new Warrior (new Properties ("player",50,100,200,200));

    Transform tf;
    tf.Log();
    return m_IsRunning = true;
}

void Engine::Update(){
   if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
   {
    SDL_Log("Key A pushed!");
   }
    player->Update(0);
}

void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 124, 418, 954, 955);             //Màu nền của gamme
    SDL_RenderClear(m_Renderer);                                        //Xóa bỏ nền đen mặc định gây nhiều lỗi

    // render texture
    player->Draw();
   SDL_RenderPresent(m_Renderer);                                       //Update m_Renderer lên màn hình sau khi nó được tạo mới
}

void Engine::Events(){
  Input::GetInstance()->Listen();
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();         //Clean của TextủeManager
    SDL_DestroyRenderer(m_Renderer);                //Clean Renderer
    SDL_DestroyWindow(m_Window);                    //Clean Window
    IMG_Quit();                                       //thoát khỏi sdl img
    SDL_Quit();                                     //thoát khỏi sdl
}

void Engine::Quit(){            //dùng trong function Events của class engine
    m_IsRunning = false;
}
