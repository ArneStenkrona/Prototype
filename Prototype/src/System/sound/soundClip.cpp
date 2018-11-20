#include "soundClip.h"

SoundClip::SoundClip(std::string _filePath)
    : path(_filePath)
{
    //Load sound effects
    chunk = Mix_LoadWAV(path.c_str());
    if (chunk == NULL)
    {
        printf("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
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
