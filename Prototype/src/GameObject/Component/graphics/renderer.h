#pragma once
#include "GameObject\Component\component.h"
#include "GameObject\Component\geometry\position.h"

class GameObject;
class Renderer : public Component {
public:
    Renderer(GameObject *_object);

    ~Renderer();

    void onActivate();
    void onDeactivate();
    void start();
    void update();

    void setRenderLayer(unsigned int layer);
    unsigned int getRenderLayer() const { return renderLayer; }

    static void setCamera(GameObject *_camera);
    static GameObject *mainCamera;

    inline static Point getCameraPosition() { return cameraPosition->position; }

    virtual void render();

protected:
    static Position *cameraPosition;

    int renderLayer;
};