#include "parallaxBackground.h"
#include <algorithm>

ParallaxBackground::ParallaxBackground(Point _origin): origin(_origin), depthOfField(10)
{
}

ParallaxBackground::~ParallaxBackground()
{
    parallaxLayers.clear();
}

void ParallaxBackground::renderParallaxLayers(Point position)
{
    background->render(0, 0);
    for each (tuple<LTexture*, double, bool> layer in parallaxLayers) {
        //offset / (distance * depthOfField)
        //Point textureDim = Point(get<0>(layer)->getHeight(), get<0>(layer)->getHeight());
        Point renderPosition;
        if (get<2>(layer)) {
            renderPosition = (origin - Point(position.x, 0)) * (1 / (get<1>(layer) * depthOfField));
        }
        else {
            renderPosition = (origin - position) * (1 / (get<1>(layer) * depthOfField));
        }
        get<0>(layer)->render(renderPosition.x, renderPosition.y);
    }
}

void ParallaxBackground::setDepthOfField(double d)
{
    depthOfField = d;
}

void ParallaxBackground::addLayer(LTexture * texture, double depth, bool fixVertical)
{
    parallaxLayers.push_back({ texture, depth, fixVertical });

    sort(begin(parallaxLayers), end(parallaxLayers), [](auto const &t1, auto const &t2) {
        return get<1>(t1) > get<1>(t2);
    });
}

void ParallaxBackground::addBackground(LTexture * bg)
{
    background = bg;
}

void ParallaxBackground::setOrigin(Point p)
{
    origin = p;
}
