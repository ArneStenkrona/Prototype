#pragma once
#include <tuple>
#include <vector>
#include "math\point.h"
#include "lTexture.h"

using namespace::std;
class ParallaxBackground {
public:
    ParallaxBackground(Point _origin);
    ~ParallaxBackground();

    //Layers are rendered at an offset relative to the origin
    void renderParallaxLayers(Point position);
    void setDepthOfField(double d);

    void addLayer(LTexture *l, double depth, bool fixVertical = false);

    void addBackground(LTexture *bg);

    void setOrigin(Point p);

private:
    //The layers are centered at the origin
    Point origin;

    //Background that will be rendered first and without parallax scrolling
    LTexture *background;
    //Tuple consisting of LTexture: parallax layers, double: layer depth:, bool: fix vertical movement
    //Sorted in descending order
    vector<tuple<LTexture*, double, bool>> parallaxLayers;

    double depthOfField;
};