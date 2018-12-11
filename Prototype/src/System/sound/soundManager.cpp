#include "soundManager.h"
const std::string SoundManager::soundPaths[SoundManager::TOTAL_SOUNDS] = {"Assets/Sound/sound/default/arugh.wav",
                                                                          "Assets/Sound/sound/prt/laser.wav",
                                                                          "Assets/Sound/sound/prt/thud.wav",
                                                                          "Assets/Sound/sound/prt/footstep.wav",
                                                                          "Assets/Sound/sound/prt/glass_cracking.wav",
                                                                          "Assets/Sound/sound/prt/glass_shatter.wav" };
std::vector<SoundClip*> SoundManager::soundClips;

const std::string SoundManager::musicPaths[SoundManager::TOTAL_MUSIC] = { "Assets/Sound/music/default/untitled.mid",
                                                                          "Assets/Sound/music/prt/window.mid",
                                                                          "Assets/Sound/music/prt/lab.mid",
                                                                          "Assets/Sound/music/editor/editor.mid" };
std::vector<MusicClip*> SoundManager::musicClips;

SoundManager::MUSIC SoundManager::currentMusic = TOTAL_MUSIC;

void SoundManager::initalizeSoundManager()
{
    MusicClip::initialize();

    soundClips.resize(TOTAL_SOUNDS);
    for (int i = 0; i < TOTAL_SOUNDS; i++) {
        soundClips[i] = (new SoundClip(soundPaths[i]));
    }
    musicClips.resize(TOTAL_MUSIC);
    for (int i = 0; i < TOTAL_MUSIC; i++) {
        musicClips[i] = (new MusicClip(musicPaths[i]));
    }
}

void SoundManager::closeSoundManager()
{
    soundClips.clear();
    musicClips.clear();
}

void SoundManager::playMusic(MUSIC music)
{
    if (music == TOTAL_MUSIC) {
        musicClips[currentMusic]->stop();
    }
    if (music == currentMusic) {
        return;
    }
    else {
        musicClips[currentMusic]->stop();
        musicClips[music]->play();
    }
    currentMusic = music;
}