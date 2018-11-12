#include "soundManager.h"

const std::string SoundManager::soundPaths[SoundManager::TOTAL_SOUNDS] = {"Assets/Sound/default/arugh.wav",
                                                                          "Assets/Sound/prt/laser.wav",
                                                                          "Assets/Sound/prt/thud.wav",
                                                                          "Assets/Sound/prt/footstep.wav" };
std::vector<SoundClip*> SoundManager::soundClips;

void SoundManager::initalizeSoundManager()
{
    soundClips.resize(TOTAL_SOUNDS);
    for (int i = 0; i < TOTAL_SOUNDS; i++) {
        soundClips[i] = (new SoundClip(soundPaths[i]));
    }
}

void SoundManager::closeSoundManager()
{
    soundClips.clear();
}
