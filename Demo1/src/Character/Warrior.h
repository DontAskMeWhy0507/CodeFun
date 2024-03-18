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
         Animation* m_Animation;
         Rigidbody* m_RigidBody;
};

#endif // WARRIOR_H
