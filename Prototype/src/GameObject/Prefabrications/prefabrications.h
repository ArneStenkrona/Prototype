#pragma once
#include "prefabrication.h"

class Character : public Prefabrication {
public:
    Character();
    GameObject* instantiate() const;
};

class MuzzleFlash : public Prefabrication {
public:
    MuzzleFlash();
    GameObject* instantiate() const;
};

class Shrapnel : public Prefabrication {
public:
    Shrapnel();
    GameObject* instantiate() const;
};

class LaserBeam : public Prefabrication {
public:
    LaserBeam();
    GameObject* instantiate() const;
};

class GlassContainer : public Prefabrication {
public:
    GlassContainer();
    GameObject* instantiate() const;
};

class DoorPrefab : public Prefabrication {
public:
    DoorPrefab();
    GameObject* instantiate() const;
};