#pragma once
#include "prefabrication.h"

class Character : public Prefabrication {
public:
    Character();
    GameObject* instantiate();
};

class MuzzleFlash : public Prefabrication {
public:
    MuzzleFlash();
    GameObject* instantiate();
};

class Shrapnel : public Prefabrication {
public:
    Shrapnel();
    GameObject* instantiate();
};

class LaserBeam : public Prefabrication {
public:
    LaserBeam();
    GameObject* instantiate();
};

class GlassContainer : public Prefabrication {
public:
    GlassContainer();
    GameObject* instantiate();
};