#include "SoundManager.h"
SoundManager* SoundManager::s_Instance = nullptr;


int SoundManager::LoadMusic(const char* filename)
{
    Mix_Music *m = nullptr;
    m = Mix_LoadMUS(filename);
    if (m = nullptr)
    {
        std::cerr << Mix_GetError() << std::endl;
        return -1;
    }
    music.push_back(m);
    return music.size()-1;
}
int SoundManager::LoadSound(const char * filename)
{
    Mix_Chunk *m = nullptr;
    m = Mix_LoadWAV(filename);
    if (m = nullptr)
    {
        std::cerr << Mix_GetError() << std::endl;
        return -1;
    }
    sounds.push_back(m);
    return sounds.size()-1;
}

void SoundManager::SetVolume (int v)
{
    volume = (MIX_MAX_VOLUME*v)/100;
}

int SoundManager::PlayMusic(int m)
{
    if(Mix_PlayingMusic() == 0)
    {
        Mix_Volume(1,volume);
        Mix_PlayMusic(music[m],-1);
    }
    return 0;
}
int SoundManager::PlaySound(int s)
{
      if(Mix_PlayingMusic() == 0)
    {
        Mix_Volume(-1,volume);
        Mix_PlayChannel(-1,sounds[s],0);
    }
    return 0;
}

int SoundManager::InitMixer()
{
    Mix_Init(MIX_INIT_MP3);
    SDL_Init(SDL_INIT_AUDIO);
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0)
    {
        std::cerr << Mix_GetError() << std::endl;
        return -1;
    }
    SetVolume(80);
    return 0;
}

void SoundManager::quitMixer()
{
    for(int s = 0; s < sounds.size(); s++)
    {
        Mix_FreeChunk(sounds[s]);
        sounds[s] = nullptr;
    }
    for(int s = 0; s < music.size(); s++)
    {
        Mix_FreeMusic(music[s]);
        music[s] = nullptr;
    }
    Mix_Quit();
}

void SoundManager::togglePlay()
{
    if(Mix_PausedMusic() == true){
        Mix_ResumeMusic();
    }
    else {
        Mix_PausedMusic() ;
    }
}






    