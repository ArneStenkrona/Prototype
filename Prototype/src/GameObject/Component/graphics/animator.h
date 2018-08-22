#pragma once
#include "GameObject\Component\component.h"
#include "System\graphics\animationClip.h"
#include <map>
#include <string>
using namespace::std;

//The animator component is made for easy communication with sprites
class Animator : Component {
public:
    Animator(GameObject * _object);

    void start();
    void update();
    void updateComponents();

    void addClip(string name, AnimationClip *clip);
    void removeClip(string name);

    void setClip(string clipName);

private:
    //The clip currently playing
    AnimationClip *currentClip;
    //Dictionary that binds a clip name to a clip
    map<string, AnimationClip*> animationClips;
};