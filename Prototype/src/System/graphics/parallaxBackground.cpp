#include "parallaxBackground.h"
#include <algorithm>

ParallaxBackground::ParallaxBackground(Point _origin): origin(_origin), depthOfField(10)
{
}

ParallaxBackground::~ParallaxBackground()
{
}

void ParallaxBackground::renderParallaxLayers(Point position)
{
    background->render(0, 0);
    for each (tuple<LTexture*, double> layer in parallaxLayers) {
        //offset / (distance * depthOfField)
        Point renderPosition = (origin - position) * (1 / (get<1>(layer) * depthOfField));
        get<0>(layer)->render(renderPosition.x, renderPosition.y);
    }
}

void ParallaxBackground::setDepthOfField(double d)
{
    depthOfField = d;
}

void ParallaxBackground::addLayer(LTexture * texture, double depth)
{
    parallaxLayers.push_back({ texture, depth });

    sort(begin(parallaxLayers), end(parallaxLayers), [](auto const &t1, auto const &t2) {
        return get<1>(t1) < get<1>(t2);
    });
}

void ParallaxBackground::addBackground(LTexture * bg)
{
    background = bg;
}
