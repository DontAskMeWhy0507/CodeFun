
#include <string>
#include "SDL.h"

class Animation 
{
    public:
     Animation(){}
     void Update();
     void Draw(float x, float y, int spritWidth, int spriteHeight);
     void SetProps(std::string textureID, int spritRow,int frameCount, int aimSpeed, SDL_RendererFlip flip= SDL_FLIP_NONE);
    
    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AimSpeed,m_FrameCount;        
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() /  m_AimSpeed) % m_FrameCount);
}

void Animation::Draw(float x, float y,int spritWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureID, int spritRow,int frameCount, int aimSpeed, SDL_RendererFlip flip)
{
    m_TextureID = textureID;
    m_SpriteRow = spritRow;
    m_FrameCount = frameCount;
    m_AimSpeed = aimSpeed;
    m_Flip = flip;
}


//file warrior.h #include "Animation.h"
//ở cuối dòng private thê Animation* m_Animation; và bỏ đi 2 dòng ở trên;

//file warrior.cpp 
/*
xoá bỏ 3 dòng code trong Warrior::Warrior():Character 
thêm m_Animation= new Animation();
m_Animation->SetProps(m_TextureID,1,6,80,SDL_FLIP_HORIZONTAL);
*/
/*xoá bỏ 1 dòng trong void Warrior::Draw()
thêm m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
*/

/*xoá bỏ 1 dòng trong void Warrior::Update()
thêm m_Animation->Update();
*/