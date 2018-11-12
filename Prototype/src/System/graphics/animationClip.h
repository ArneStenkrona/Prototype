#pragma once
#include <string>
#include <map>
#include "System\sound\soundManager.h"
struct AnimationClip {
    std::string name;
    //index of first frame of sprite
    int startIndex;
    //index of last frame of sprite
    int endIndex;
    //How many in-game frames will it take to play on frame of animation
    int frameFactor;
    //Mapping from frame to sound to be played on that frame;
    std::map<int, SoundManager::SOUNDS> sounds;
};
