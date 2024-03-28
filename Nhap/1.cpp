#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"

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
                    m_KeyDownTime += 0.2;

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


Warrior::Warrior(Properties* props):Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();                     //Collinder ở trong Physics.
    m_Collider->SetBuffer(-90, -70, 0, 0);          //thay đổi giá trị buffer để collider không bị lệch so với nhân vật
    m_RigidBody =  new Rigidbody();
    m_RigidBody->SetGravity(5.0f);



     m_Animation= new Animation();
    m_Animation->SetProps(m_TextureID,1,8,80);
    //(m_texture,1 row,8 frames,80ms ,SDL_FLIP_HORIZONTAL); thêm dấu phải trong ngoặc () nữa để flip
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);

    //Hiển thị collider
   /* Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);*/
}



void Warrior::Update(float dt)
{
   (!m_TraiPhai) ?  m_Animation->SetProps("player",1,8,100) : m_Animation->SetProps("player",1,8,100,SDL_FLIP_HORIZONTAL);
       m_HoldTime  = Input::GetInstance()->GetKeyDownTime();
       m_LastHoldTime = (m_HoldTime> m_LastHoldTime)? m_HoldTime : m_LastHoldTime;

    m_RigidBody->UnSetForce();

    //Run backward
     if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)&&m_IsGrounded == true)
   {
           m_RigidBody->ApplyForceX(3*BACKWARD);
           m_LastDirection = 1;
           m_TraiPhai = true;

        m_Animation->SetProps("player_run",1,8,100,SDL_FLIP_HORIZONTAL);
   }

   //Run forward
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)&&m_IsGrounded == true)
   {
           m_RigidBody->ApplyForceX(3*FORWARD);
           m_LastDirection = -1;
                      m_TraiPhai = false;


        m_Animation->SetProps("player_run",1,8,100);
   }
   //jump

   bool Release () 
   {
    if(m_HoldTime == 0 && m_IsGrounded && m_LastHoldTime > 0) return true;
    return false;
   }

    JumpLeft(){}
    JumpRight(){}


  
   if (!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_KeyDownTime > 0) {
        // Perform a jump
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
            m_RigidBody->ApplyForceX(5*FORWARD);
            m_LastDirection = -1;
        } else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
            m_RigidBody->ApplyForceX(5*BACKWARD);
            m_LastDirection = 1;
        }
        // Reset m_KeyDownTime
        m_KeyDownTime = 0;
    }
if(m_IsJumping && m_JumpTime > 0 && (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)||Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))) {
    m_JumpTime -= dt;
    m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_RigidBody->ApplyForceX(5*FORWARD);
                 m_LastDirection = -1;

    } else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_RigidBody->ApplyForceX(5*BACKWARD);
                 m_LastDirection = 1;

    }
    m_Animation->SetProps("Jump",1,2,100);
} else {
    m_IsJumping = false;
    m_JumpTime = JUMP_TIME;


}
if( m_LastDirection == 1 && !m_IsGrounded )     m_RigidBody->ApplyForceX(5*BACKWARD);
    else if(m_LastDirection == -1&& !m_IsGrounded ) m_RigidBody->ApplyForceX(5*FORWARD);

if(    m_IsGrounded &&!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)  && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )  m_LastDirection = 0;


    //move on x axis


    m_RigidBody->Update(dt);                            // truyền dt vào là thông số thời gian trôi qua để tính vận tốc và vị wtrí
        m_LastSafePosition.X = m_Transform->X;          // lưu lại vị trí an toàn trước khi di chuyển

    m_Transform->X += m_RigidBody->Position().X;       // hàm này để tăng giá trị của x trong m_Transform sau khi thay đỏi m_RigidBody
    //  m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);
    //dùng để kiểm tra va chạm với map. 18,50 là kích thước của collider


    //Kiểm tra va chạm với map. Nếu va chạm với map thì trả lại vị trí ban đầu trước đó.
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))        //Nếu va chạm với map return true
        m_Transform->X = m_LastSafePosition.X;


    // move on Y axis

    m_RigidBody->Update(dt);

    m_LastSafePosition.Y = m_Transform->Y;

    m_Transform->Y += m_RigidBody->Position().Y;

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }


    //Thay đổi m_Origin khi nhân vật di chuyển.
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    m_Animation->Update();              //Cập nhật lại giá trị dt
}

void Warrior::Clean()
{
    TextureManager::GetInstance() ->Clean();
}
