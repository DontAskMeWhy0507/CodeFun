#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"

class CollisionHandler{

    public:
        bool MapCollision(SDL_Rect a);
        bool CheckCollision(SDL_Rect a, SDL_Rect b);

        inline static CollisionHandler* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler();}

    private:
        CollisionHandler();
        TileMap m_CollisionTilemap;     // Là vector 2 chiều chứa thông tin về các tile trong map.
        TileLayer* m_CollisionLayer;    //là layer chứ thông tin của map.
        static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H
