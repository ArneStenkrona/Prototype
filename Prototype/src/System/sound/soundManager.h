#pragma once
#include "soundClip.h"
#include "musicClip.h"
#include <vector>

class SoundManager {
public:
    static enum SOUNDS
    {
        DEFAULT_SOUND,
        LASER_SOUND,
        THUD_SOUND,
        FOOTSTEP_SOUND,
        GlASS_CRACKING_SOUND,
        GlASS_SHATTER_SOUND,
        TOTAL_SOUNDS
    };
    static enum MUSIC
    {
        DEFAULT_MUSIC,
        WINDOW_MUSIC,
        LAB_MUSIC,
        TOTAL_MUSIC
    };

    static void initalizeSoundManager();
    //Should only be closed when application exits
    static void closeSoundManager();

    inline static SoundClip* getSound(SOUNDS sound) { return soundClips[sound]; }

    inline static void playMusic(MUSIC music) { musicClips[music]->play(); }

private:
    static const std::string soundPaths[TOTAL_SOUNDS];
    static std::vector<SoundClip*> soundClips;
    static const std::string musicPaths[TOTAL_MUSIC];
    static std::vector<MusicClip*> musicClips;
};