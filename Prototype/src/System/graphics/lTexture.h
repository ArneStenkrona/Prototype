#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "color.h"

class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path, SDL_Renderer* renderer);
    //Creates blank texture
    bool createBlank(int width, int height, SDL_Renderer* renderer, SDL_TextureAccess = SDL_TEXTUREACCESS_TARGET);
    //Set self as render target
    void setAsRenderTarget(SDL_Renderer* renderer);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y);

    //Renders texture at given point with rotation and flip
    void renderEx(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Renders the tile in the texture given by the tileQuad
    //x and y is the position
    //widthFactor and heightFactor determine how many tiles to take
    void renderTile(int x, int y, int tileIndex, int widthFactor = 1, int heightFactor = 1, 
                    bool mirrorH = false, bool mirrorV = false, double rotation = 0, int pivotX = 0, int pivotY = 0,
                    Color color = COLOR_WHITE) const;


    void renderText(int x, int y, std::string text) const;
    void renderText(int x, int y, std::string text, Color color) const;


    //Renders the tile in the texture given by the tileQuad with roation and flip
    void renderTileEx(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Rect *tileQuad = NULL);

    //Renders texture with center at given point
    void renderCenter(int x, int y);

    //Gets image dimensions
    inline int getWidth() const { return mWidth; };
    inline int getHeight() const { return mHeight; };

private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    //Image dimensions
    int mWidth;
    int mHeight;

    //How many tiles can be fitted per row
    unsigned int tilesPerRow;
};