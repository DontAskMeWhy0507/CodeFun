#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"


Warrior::Warrior(Properties* props):Character(props)
{
    /*m_Row = 1;
    m_FrameCount = 6;
    m_AnimaSpeed = 180;*/
    m_RigidBody =  new Rigidbody();
     m_Animation= new Animation();
m_Animation->SetProps(m_TextureID,1,8,80);//(m_texture,1 row,8 frames,80ms ,SDL_FLIP_HORIZONTAL); thêm dấu phải trong ngoặc () nữa để flip
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
}



void Warrior::Update(float dt)
{
    m_Animation->SetProps("player",1,8,100);
    m_RigidBody->UnSetForce();

     if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
   {
           m_RigidBody->ApplyForceX(5*BACKWARD);

        m_Animation->SetProps("player_run",1,8,100,SDL_FLIP_HORIZONTAL);
   }
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
   {
           m_RigidBody->ApplyForceX(5*FORWARD);

        m_Animation->SetProps("player_run",1,8,100);
   }



    m_RigidBody->Update(dt);                            // truyền dt vào là thông số thời gian trôi qua để tính vận tốc và vị wtrí
     m_Transform->TranslateX(m_RigidBody->Position().X);        // hàm này để tăng giá trị của x trong m_Transform sau khi thay đỏi m_RigidBody
  //  m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;

    m_Animation->Update();              //Cập nhật lại giá trị dt
}

void Warrior::Clean()
{
    TextureManager::GetInstance() ->Clean();
}
