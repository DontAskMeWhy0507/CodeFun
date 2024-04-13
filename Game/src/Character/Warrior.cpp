#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "Camera.h"

#include <iostream>

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
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}



void Warrior::Update(float dt)
{
   //Xử lý trái phải ide
   (!m_TraiPhai) ?  m_Animation->SetProps("player",1,8,100) : m_Animation->SetProps("player",1,8,100,SDL_FLIP_HORIZONTAL);

    //tính thời gian lưu
    SoMoi  = Input::GetInstance()->GetKeyDownTime();
    if( SoCu != 0.0f && SoMoi == 0.0f )
    {
        IsTheKeyReleased = true;
        luu = SoCu;
    }
    else IsTheKeyReleased = false;

    m_RigidBody->UnSetForce();

    //Run backward
     if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)&&m_IsGrounded == true && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
   {
           m_RigidBody->ApplyForceX(3.0f*BACKWARD);
           m_LastDirection = -1.0f;
           m_TraiPhai = true;

        m_Animation->SetProps("player_run",1,8,100,SDL_FLIP_HORIZONTAL);
   }

   //Run forward
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)&&m_IsGrounded == true&& !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE ))
   {
           m_RigidBody->ApplyForceX(3.0f*FORWARD);
           m_LastDirection = 1.0f;
                      m_TraiPhai = false;


        m_Animation->SetProps("player_run",1,8,100);
   }
   //jump


    std::cout<<"Somoi "<<SoMoi<<' '<<"SoCu "<<SoCu<<" SoLuu "<<luu<<std::endl;

        //Kiểm tra xem là nhảy lên,nhảy trái hay nhảy phải.
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)&&m_IsGrounded)
        {
            IsJumpUp = false;
            IsJumpRight = true;
            IsJumpLeft = false;
        }
        else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)&&m_IsGrounded)
        {
            IsJumpUp = false;
            IsJumpRight = false;
            IsJumpLeft = true;


        }
       else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&m_IsGrounded)
        {
            IsJumpUp = true;
            IsJumpRight = false;
            IsJumpLeft = false;
        }


           //Xử lý nhảy
        if(BounceTop == true ) luu = 0.0f;

        if(IsJumpUp && luu > 0.0f)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            luu -=dt;
            m_Animation->SetProps("Jump",1,2,100);
        }
        else if(IsJumpRight && luu > 0)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            m_RigidBody->ApplyForceX(FORWARD*(31.0f-luu)/3.0f*m_Direction);
            luu -=dt;
            m_Animation->SetProps("Jump",1,2,100);
            m_LastDirection = 1.0f;

        }

        else if (IsJumpLeft && luu >0)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            m_RigidBody->ApplyForceX(BACKWARD*(31.0f-luu)/3.0f*m_Direction);
            luu -=dt;
            m_Animation->SetProps("Jump",1,2,100,SDL_FLIP_HORIZONTAL);
            m_LastDirection = -1.0f;

        }
        else
        {
            m_IsJumping = false;
        }

        //Kiểm tra xem có đang rơi  không
        if(m_RigidBody->Velocity().Y > 0 && !m_IsGrounded)
        {
           m_IsFalling = true;
        }
        else    m_IsFalling = false;

        //Xử lý rơi
    if( m_LastDirection == 1.0f && m_IsFalling   )   {  m_RigidBody->ApplyForceX(2.0f*FORWARD/m_Direction);              m_Animation->SetProps("Fall",1,2,100);}
    else if(m_LastDirection == -1.0f&& m_IsFalling ) {m_RigidBody->ApplyForceX(2.0f*BACKWARD/m_Direction);                       m_Animation->SetProps("Fall",1,2,100,SDL_FLIP_HORIZONTAL);}
    else if(m_LastDirection == 0.0f&& m_IsFalling)     m_Animation->SetProps("Fall",1,2,100);
    if( m_IsGrounded &&!Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)  && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )  m_LastDirection = 0.0f;





    //move on x axis


    m_RigidBody->Update(dt);                            // truyền dt vào là thông số thời gian trôi qua để tính vận tốc và vị wtrí
        m_LastSafePosition.X = m_Transform->X;          // lưu lại vị trí an toàn trước khi di chuyển

    m_Transform->X += m_RigidBody->Position().X;       // hàm này để tăng giá trị của x trong m_Transform sau khi thay đỏi m_RigidBody
    //  m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);
    //dùng để kiểm tra va chạm với map. 18,50 là kích thước của collider


    //Kiểm tra va chạm với map. Nếu va chạm với map thì trả lại vị trí ban đầu trước đó.
    if(CollisionHandler::GetInstance()->MapCollisionWall(m_Collider->Get()))        //Nếu va chạm với map return true
      {
        if(!m_IsGrounded)
        {
            m_Direction = -1.0f;
             m_Transform->X = m_LastSafePosition.X;
        }

        else
        {
            m_Transform->X = m_LastSafePosition.X;
        }

      }

    // move on Y axis

    m_RigidBody->Update(dt);

    m_LastSafePosition.Y = m_Transform->Y;

    m_Transform->Y += m_RigidBody->Position().Y;

    m_Collider->Set(m_Transform->X, m_Transform->Y, 18, 50);



     if(CollisionHandler::GetInstance()->MapCollisionGround(m_Collider->Get()))
    {
        m_IsCeiling = false;
        m_IsGrounded = true;
        BounceTop = false;
        BounceWall = false;
        m_Direction = 1.0f;

        m_Transform->Y = m_LastSafePosition.Y;
    }
    else if (CollisionHandler::GetInstance()->MapCollisionCeiling(m_Collider->Get()))
    {
        m_IsCeiling = true;
        m_IsGrounded = false;
        BounceTop = true;
    }
    else
    {
        m_IsGrounded = false;
        BounceTop = false;

    }

    //Thay đổi m_Origin khi nhân vật di chuyển.
    m_Origin->X = m_Transform->X + m_Width/2.0f;
    m_Origin->Y = m_Transform->Y + 0.5f*m_Height;

    m_Animation->Update();              //Cập nhật lại giá trị dt

    SoCu = SoMoi;
}

void Warrior::Clean()
{
    TextureManager::GetInstance() ->Clean();
}
