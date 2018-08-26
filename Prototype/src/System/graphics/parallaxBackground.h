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

    void addLayer(LTexture *l, double depth);

    void addBackground(LTexture *bg);

    void setOrigin(Point p);

private:
    //The layers are centered at the origin
    Point origin;

    //Background that will be rendered first and without parallax scrolling
    LTexture *background;
    //Tuple consisting of parallax layers and their respective depths
    //Sorted in descending order
    vector<tuple<LTexture*, double>> parallaxLayers;

    double depthOfField;
};