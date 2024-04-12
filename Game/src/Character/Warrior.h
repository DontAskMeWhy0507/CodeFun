#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"

#define JUMP_FORCE 10.0f
#define JUMP_TIME 20.0f;

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        void Draw() ;
        void Clean() ;
        void Update(float dt) ;

   private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsCeiling;
        bool m_IsWall;
        bool m_IsGrounded;
        bool m_IsCrouching;
        bool m_TraiPhai;
        bool BounceTop;
        bool BounceWall;


        bool IsJumpRight;
        bool IsJumpLeft;
        bool IsJumpUp;
        bool IsTheKeyReleased;




        float m_Direction = 1;
        float SoMoi, SoCu;
        float luu;



        float m_JumpTime;
        float m_JumpForce;
        float m_LastDirection = 0;
        float m_HoldTime;
        float m_LastHoldTime;





        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif // WARRIOR_H
