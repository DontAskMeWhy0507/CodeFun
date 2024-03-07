#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"

class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        void Draw() ;
        void Clean() ;
        void Update(float dt) ;

    private:
         //int m_Row, m_Frame, m_FrameCount;
         //int m_AnimaSpeed;
         Animation* m_Animation;
         Rigidbody* m_RigidBody;
};

#endif // WARRIOR_H
