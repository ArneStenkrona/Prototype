#include "soundClip.h"

SoundClip::SoundClip(std::string _filePath)
{
    //Load sound effects
    chunk = Mix_LoadWAV(_filePath.c_str());
    if (chunk == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

SoundClip::~SoundClip()
{
    if (chunk)
        Mix_FreeChunk(chunk);
}

void SoundClip::play(int channel, int repeat) const
{
    Mix_PlayChannel(channel, chunk, repeat);
}
