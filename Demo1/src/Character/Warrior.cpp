#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"

Warrior::Warrior(Properties* props):Character(props)
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();                     //Collinder ở trong Physics.
    m_Collider->SetBuffer(-90, -70, 0, 0);          //thay đổi giá trị buffer để collider không bị lệch so với nhân vật
    m_RigidBody =  new Rigidbody();
    m_RigidBody->SetGravity(3.0f);


     m_Animation= new Animation();
    m_Animation->SetProps(m_TextureID,1,8,80);
    //(m_texture,1 row,8 frames,80ms ,SDL_FLIP_HORIZONTAL); thêm dấu phải trong ngoặc () nữa để flip
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
    
    //Hiển thị collider
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}



void Warrior::Update(float dt)
{
    m_Animation->SetProps("player",1,8,100);
    m_RigidBody->UnSetForce();

    //Run backward
     if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
   {
           m_RigidBody->ApplyForceX(5*BACKWARD);

        m_Animation->SetProps("player_run",1,8,100,SDL_FLIP_HORIZONTAL);
   }

   //Run forward
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
   {
           m_RigidBody->ApplyForceX(5*FORWARD);

        m_Animation->SetProps("player_run",1,8,100);
   }

    // Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);

    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
        m_Animation->SetProps("Jump",1,2,100);

    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //move on x axis


    m_RigidBody->Update(dt);                            // truyền dt vào là thông số thời gian trôi qua để tính vận tốc và vị wtrí
        m_LastSafePosition.X = m_Transform->X;          // lưu lại vị trí an toàn trước khi di chuyển

    m_Transform->X += m_RigidBody->Position().X;       // hàm này để tăng giá trị của x trong m_Transform sau khi thay đỏi m_RigidBody
    //  m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);
    //dùng để kiểm tra va chạm với map. 18,50 là kích thước của collider
    

    //Kiểm tra va chạm với map
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
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
