#include "lTexture.h"
#include "System\graphics\graphicsEngine.h"
#include "World\Tile.h"

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
                          bool mirrorH, bool mirrorV, double rotation, int px, int py) const
{
    //Check if visible in viewport
    if (x > GraphicsEngine::getActiveWindow()->getWidth() / GraphicsEngine::SCALE_X || 
        y > GraphicsEngine::getActiveWindow()->getHeight() / GraphicsEngine::SCALE_Y ||
        x + Tile::TILE_SIZE * widthFactor < 0 || y + Tile::TILE_SIZE * heightFactor < 0) return;

    SDL_Rect renderQuad = { x, y, Tile::TILE_SIZE * widthFactor, Tile::TILE_SIZE * heightFactor };
    SDL_Rect tileRect = { ((tileIndex * widthFactor) % tilesPerRow) * Tile::TILE_SIZE, 
                          ((tileIndex * heightFactor) / tilesPerRow) * Tile::TILE_SIZE, 
                          Tile::TILE_SIZE * widthFactor, 
                           Tile::TILE_SIZE * heightFactor };

    SDL_Point pivot = { px, py };
    
    if (mirrorH && mirrorV)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation + 90, &pivot, SDL_FLIP_NONE);
    else if (mirrorH)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_HORIZONTAL);
    else if (mirrorV)
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_VERTICAL);
    else SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, &pivot, SDL_FLIP_NONE);
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