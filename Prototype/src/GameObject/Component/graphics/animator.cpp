#include "animator.h"
#include "GameObject/gameObject.h"
#include <iostream>

AnimationClip nullclip = {"nullclip", 0,0,1 };

Animator::Animator(GameObject * _object) : Component(_object), transitionFrames(0),
inTransition(false), animationSpeedFactor(1), currentClip(&nullclip)
{
    sprite = requireComponent<Sprite>();
}

void Animator::start()
{
}

void Animator::update()
{
    //Handle clips
    if (inTransition) {     
        transitionFrames -= 1 / animationSpeedFactor;

        if ((int)(transitionFrames * animationSpeedFactor) < 0) {
            playQueued();
        }
    }
    //Handle sprite
    if (!(currentClip->startIndex == currentClip->endIndex || 
        currentClip->startIndex == -1 || currentClip->endIndex == -1)) {
        if (frameFactorCounter >= currentClip->frameFactor * animationSpeedFactor) {
            frameFactorCounter = 0;
            sprite->tileIndex++;
            if (sprite->tileIndex > currentClip->endIndex) 
                sprite->tileIndex = currentClip->startIndex;
        }
        frameFactorCounter++;
    }
    
}

void Animator::updateComponents()
{
    sprite = (object->hasComponent<Sprite>()) ? object->getComponent<Sprite>() : sprite;
}

void Animator::addClip(AnimationClip  clip)
{
    animationClips[clip.name] = clip;
}

void Animator::removeClip(string name)
{
    animationClips.erase(name);
}

void Animator::setSpeedFactor(double factor)
{
    animationSpeedFactor = factor;
}

void Animator::playClip(string clipName, bool transition, bool restart)
{
    if (!restart && clipName == currentClip->name) return;
        queuedClip = &animationClips[clipName];
    if (transition) {
        transitionFrames = (currentClip->endIndex - sprite->tileIndex) * currentClip->frameFactor;
        inTransition = true;
    }
    else {
        playQueued();
    }
}

void Animator::playQueued()
{
    if (queuedClip) {
        transitionFrames = -1;
        currentClip = queuedClip;
        queuedClip = nullptr;
        sprite->tileIndex = currentClip->startIndex;
        inTransition = false;
    }
}
