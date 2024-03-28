#include <iostream>
bool IsJumpRight;
bool IsJumpLeft;
bool IsJumpUp;
bool IsTheKeyReleased;
int main() 
{
    float SoMoi, SoCu;
    int luu;
    //Kiểm tra xem phím space đã được thả ra chưa.
    if(SoMoi <= SoCu && SoCu != 0 )
    {
        IsTheKeyReleased = true;
        luu = SoCu;
    }
    else IsTheKeyReleased = false;

        //Kiểm tra xem là nhảy lên,nhảy trái hay nhảy phải.
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            IsJumpUp = true;
            if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
            {
                IsJumpRight = true;
                IsJumpUp = false;
            }
            else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
            {
                IsJumpLeft = true;
                IsJumpUp = false;
            }
          
        }    
        if(IsJumpUp && luu != 0)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            luu -=dt;
            m_Animation->SetProps("Jump",1,2,100); 
        }
        else if(IsJumpRight && luu != 0)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            m_RigidBody->ApplyForceX(FORWARD*m_JumpForce);
            luu -=dt;
            m_Animation->SetProps("Jump",1,2,100);        }
        else if (IsJumpLeft && luu != 0)
        {
            m_IsJumping = true;
            m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
            m_RigidBody->ApplyForceX(BACKWARD*m_JumpForce);
            luu -=dt;
             m_Animation->SetProps("Jump",1,2,100,SDL_FLIP_HORIZONTAL);        
        }
        else 
        {
            m_IsJumping = false;
        }
        

}


