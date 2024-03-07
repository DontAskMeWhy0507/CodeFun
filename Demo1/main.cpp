#include "Engine.h"

using namespace std;

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();              //KHOI TAO GAME
    while(Engine::GetInstance()-> IsRunning()){     //KIEM TRA XEM GAME CO DANG CHAY KHONG
        Engine ::GetInstance()->Events();           //Sự kiện từ người dùng (ví dụ như ấn X để tắt game)
        Engine ::GetInstance()->Update();              //
        Engine ::GetInstance()->Render();
    }
    Engine::GetInstance()->Clean();         //XOA DI SAU KHI CHOI XONG
   return 0;
}
