#pragma once
#include "prefabrication.h"

class Character : public Prefabrication {
public:
    Character();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};

class MuzzleFlash : public Prefabrication {
public:
    MuzzleFlash();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};

class Shrapnel : public Prefabrication {
public:
    Shrapnel();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};

class LaserBeam : public Prefabrication {
public:
    LaserBeam();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};

class GlassContainer : public Prefabrication {
public:
    GlassContainer();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};

class DoorPrefab : public Prefabrication {
public:
    DoorPrefab();
    GameObject* instantiate(std::vector<std::string> parameters = {}) const;
};