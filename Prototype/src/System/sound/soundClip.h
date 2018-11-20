#pragma once
#include <SDL_mixer.h>
#include <string>

class SoundClip {
public:
    //Create soundclip from file at file path. Only supports .wav currently
    SoundClip(std::string _filePath = "Assets/Sound/default/arugh.wav");
    ~SoundClip();

    void play(int channel = -1, int repeat = 0) const;

private:
    Mix_Chunk *chunk;
    //path where sound is stored
    const std::string path;
};