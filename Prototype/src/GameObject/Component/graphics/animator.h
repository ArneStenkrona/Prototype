#pragma once
#include "GameObject\Component\component.h"
#include "System\graphics\animationClip.h"
#include "sprite.h"
#include <map>
#include <string>
using namespace::std;

//The animator component is made for easy communication with sprites
class Animator : public Component {
public:
    Animator(GameObject * _object);

    void start();
    void update();
    void updateComponents();

    void addClip(AnimationClip clip);
    void removeClip(string name);

    void setSpeedFactor(double factor);

    //Queues a clip
    //transition determines if current clip should complete before changing to queued clip
    //restart determines if clip should be restarted if already playing
    void playClip(string clipName, bool transition, bool restart = false);

    inline std::string getCurrentClip() const { return currentClip->name; }
private:
    //The clip currently playing
    AnimationClip *currentClip;
    //The clip about to be played
    AnimationClip *queuedClip;

    //Dictionary that binds a clip name to a clip
    map<string, AnimationClip> animationClips;

    //amount of transition frames, roundest to nearest int when required
    double transitionFrames;
    //Determines if we are currently in a transition
    bool inTransition;
    //Changes the speed with which animations are played
    double animationSpeedFactor;

    Sprite *sprite;
};