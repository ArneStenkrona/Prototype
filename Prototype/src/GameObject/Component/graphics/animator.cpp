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
    if (inTransition) {     
        transitionFrames -= 1 / animationSpeedFactor;

        if ((int)(transitionFrames * animationSpeedFactor) < 0) {
            currentClip = queuedClip;
            queuedClip = nullptr;
            sprite->setAnimationIndicies(currentClip->startIndex, currentClip->endIndex);
            transitionFrames = -1;
            inTransition = false;
        }
    }
    sprite->setFrameFactor((int)(currentClip->frameFactor * animationSpeedFactor));
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
    if (transition) {
        transitionFrames = (currentClip->endIndex - sprite->getTileIndex()) * currentClip->frameFactor;
    }
    else {
        transitionFrames = -1;
    }
        inTransition = true;
        queuedClip = &animationClips[clipName];
}
