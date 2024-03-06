#include <iostream>

class Vector2D
{
    public:
      float X,Y;
    public:
        Vector2D(float x=0, float y=0): X(x), Y(y){}

    public:
        //addition +
        inline Vector2D operator+(const Vector2D& v2) const{
            return Vector2D(X+v2.X,Y+v2.Y);
        }
        //difference -
        inline Vector2D operator-(const Vector2D& v2)const{
            return Vector2D(X-v2.Y,Y-v2.Y);
        }
        //multiplication*
        inline Vector2D operator*(const float scalar)const{
            return Vector2D(X*scalar,Y*scalar);
        }

        void Log(std::string msg="")
        {
            std::cout<<msg<<"(X Y) = ("<<X<<" "<<Y<<")"<<std::endl;
        }
};


class Transform
{
    public:
        float X,Y;


    public:
        Transform(float x=0, float y=0):X(x),Y(y){}
        void Log(std::string msg = "")
        {
            std::cout<<msg<<"(X Y) = ("<<X<<" "<<Y<<")"<<std::endl;
        }

    private:
        inline void TranslateX(float x){X+=x;}
        inline void TranslateY(float y){Y+=y;}
        inline void Translate(Vector2D v){X+=v.X; Y+=v.Y;}
};




class IObject{

    public:
        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;
};


struct Properties{

    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE){
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            TextureID = textureID;
        }

    public:
        std::string TextureID;
        int Width, Height;
        float X, Y;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject {
    public:
            GameObject(Properties* props): m_TextureID(props->TextureID),
            m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip){

            m_Transform = new Transform(props->X, props->Y);
        }

        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(float dt)=0;

    protected:
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};



class Character : public GameObject
{
    public:
        Character(Properties* props): GameObject(props) {}
    virtual void Draw()=0;
    virtual void Clean()=0;
    virtual void Update(float dt)=0;


    protected:
        std::string m_Name;

};



class Warrior : public Character
{
    public:
        Warrior(Properties* props);

        void Draw() override;
        void Clean() override;
        void Update(float dt) override;

    private:
         int m_Row, m_Frame, m_FrameCount;
         int m_AnimaSpeed;
};




Warrior::Warrior(Properties* props):Character(props)
{
    m_Row = 1;
    m_FrameCount = 6;
    m_AnimaSpeed = 180;
}

void Warrior::Draw()
{
    TextureManager::GetInstance()-> DrawFrame(m_TextureID,m_Transform->X,m_Transform->Y,m_Width,m_Height,m_Row,m_Frame);
}



void Warrior::Update(float dt)
{
    m_Frame = (SDL_GetTicks()/m_AnimaSpeed)% m_FrameCount;
}

void Warrior::Clean()
{
    TextureManager::GetInstance() ->Clean();
}
