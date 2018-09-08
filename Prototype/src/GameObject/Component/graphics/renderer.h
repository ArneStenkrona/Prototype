#pragma once
#include "GameObject\Component\component.h"
#include "GameObject\Component\geometry\position.h"

class GameObject;
class Renderer : public Component {
public:
    Renderer(GameObject *_object);

    ~Renderer();

    void start();
    void update();

    void setRenderLayer(int layer);

    static void setCamera(GameObject *_camera);
    static GameObject *mainCamera;

    static Point getCameraPosition();

    virtual void render();

protected:
    static Position *cameraPosition;

    int renderLayer;
};