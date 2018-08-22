#include "animator.h"

Animator::Animator(GameObject * _object) : Component(_object)
{
}

void Animator::start()
{
}

void Animator::update()
{
}

void Animator::updateComponents()
{
}

void Animator::addClip(string name, AnimationClip * clip)
{
    animationClips[name] = clip;
}

void Animator::removeClip(string name)
{
    animationClips.erase(name);
}

void Animator::setClip(string clipName)
{
    currentClip = animationClips[clipName];
}
