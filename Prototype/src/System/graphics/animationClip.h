#pragma once
#include <string>
struct AnimationClip {
    std::string name;
    //index of first frame of sprite
    int startIndex;
    //index of last frame of sprite
    int endIndex;
    //How many in-game frames will it take to play on frame of animation
    int frameFactor;
};
