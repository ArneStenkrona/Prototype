#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "global_graphical_variables.h"

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y);

    //Renders texture at given point with rotation and flip
    void renderEx(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Renders the tile in the texture given by the tileQuad
    void renderTile(int x, int y, int tileIndex);

    //Renders the tile in the texture given by the tileQuad with roation and flip
    void renderTileEx(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect *tileQuad = NULL);

    //Renders texture with center at given point
    void renderCenter(int x, int y);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};