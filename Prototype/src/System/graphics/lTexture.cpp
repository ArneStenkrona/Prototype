#include "lTexture.h"
#include "System\graphics\graphicsEngine.h"
#include "World\Tile.h"
#include <iostream>

LTexture::LTexture() : mTexture(NULL), mWidth(0), mHeight(0), tilesPerRow(0)
{
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            tilesPerRow = mWidth / Tile::TILE_SIZE;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;

    //Return success
    return mTexture != NULL;
}

bool LTexture::createBlank(int width, int height, SDL_Renderer* renderer, SDL_TextureAccess access)
{
    //Create uninitialized texture
    mTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if (mTexture == NULL)
    {
        printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        mWidth = width;
        mHeight = height;
    }

    return mTexture != NULL;
}

void LTexture::setAsRenderTarget(SDL_Renderer* renderer)
{
    //Make self render target
    SDL_SetRenderTarget(renderer, mTexture);
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y)
{
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };
        SDL_RenderCopy(GraphicsEngine::getActiveRenderer(), mTexture, NULL, &renderQuad);
}

void LTexture::renderWavy(int x, int y, int amplitude, double phase)
{
    for (int i = 0; i < mHeight; i++) {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y + i, mWidth, mHeight };
        SDL_Rect lineQuad = { (amplitude + x + (int)(amplitude * std::sin(phase))) % mWidth , i, mWidth, 1 };
        SDL_RenderCopy(GraphicsEngine::getActiveRenderer(), mTexture, &lineQuad, &renderQuad);
    }
}

void LTexture::renderEx(int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, clip, &renderQuad, angle, center, flip);

}

void LTexture::renderTile(int x, int y, int tileIndex, int widthFactor, int heightFactor, 
                          bool mirrorH, bool mirrorV, double rotation, int pivotX, int pivotY,
                          Color color, bool scaleIndices) const
{
    SDL_SetTextureColorMod(mTexture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mTexture, color.a);

    //Check if visible in viewport
    if (x > GraphicsEngine::getActiveWindow()->getWidth() / GraphicsEngine::SCALE_X || 
        y > GraphicsEngine::getActiveWindow()->getHeight() / GraphicsEngine::SCALE_Y ||
        x + Tile::TILE_SIZE * widthFactor < 0 || y + Tile::TILE_SIZE * heightFactor < 0) return;

    SDL_Rect renderQuad = { x, y, (int)Tile::TILE_SIZE * widthFactor, (int)Tile::TILE_SIZE * heightFactor };
    //corrected index
    int ix = scaleIndices ? tileIndex * widthFactor : tileIndex;
    int iy = scaleIndices ? heightFactor : 1;
    SDL_Rect tileRect = { (ix % (int)tilesPerRow) * (int)Tile::TILE_SIZE,
                          (ix / (int)tilesPerRow) * iy * (int)Tile::TILE_SIZE,
                          (int)Tile::TILE_SIZE * widthFactor, 
                          (int)Tile::TILE_SIZE * heightFactor };

    SDL_Point pivot = { pivotX, pivotY };
    
    if (mirrorH && mirrorV)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation + 180, &pivot, SDL_FLIP_NONE);
    else if (mirrorH)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_HORIZONTAL);
    else if (mirrorV)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_VERTICAL);
    else SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_NONE);
}

void LTexture::renderText(int x, int y, std::string text) const
{
    int position = 0;
    for (char& c : text) {
        SDL_Rect renderQuad = { x + (4 * position), y, 4, mHeight };
        SDL_Rect charRect = { (int)c * 4, 0, 4, mHeight };
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &charRect, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
        position++;
    }
}

void LTexture::renderText(int x, int y, std::string text, Color color) const
{
    SDL_SetTextureColorMod(mTexture, color.r, color.g, color.b);
    renderText(x, y, text);
    SDL_SetTextureColorMod(mTexture, 255, 255, 255);
}

void LTexture::renderTileEx(int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip, SDL_Rect * tileQuad)
{

    //Entire texture
    SDL_Rect renderQuad = { x,y,mWidth,mHeight };

    //Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = tileQuad->w;
        renderQuad.h = tileQuad->h;
    }

    //Render to screen
    SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, tileQuad, &renderQuad, angle, center, flip);
}

void LTexture::renderCenter(int x, int y)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x - mWidth / 2, y - mHeight / 2, mWidth, mHeight };
    SDL_RenderCopy(GraphicsEngine::getActiveRenderer(), mTexture, NULL, &renderQuad);
}