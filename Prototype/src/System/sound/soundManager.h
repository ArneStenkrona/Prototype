#pragma once
#include "soundClip.h"
#include <vector>

class SoundManager {
public:
    static enum SOUNDS
    {
        DEFAULT,
        LASER,
        THUD,
        FOOTSTEP,
        GlASS_CRACKING,
        GlASS_SHATTER,
        TOTAL_SOUNDS
    };

    static void initalizeSoundManager();
    //Should only be closed when application exits
    static void closeSoundManager();

    inline static SoundClip* getClip(SOUNDS sound) { return soundClips[sound]; }

private:
    static const std::string soundPaths[TOTAL_SOUNDS];
    static std::vector<SoundClip*> soundClips;
};