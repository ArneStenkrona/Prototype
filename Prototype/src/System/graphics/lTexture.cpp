#include "lTexture.h"
#include "System\graphics\graphicsEngine.h"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
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
        newTexture = SDL_CreateTextureFromSurface(GraphicsEngine::getActiveRenderer(), loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
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

void LTexture::renderTile(int x, int y, int tileIndex)
{
    renderTile(x, y, tileIndex, 1, 1, false);
}

void LTexture::renderTile(int x, int y, int tileIndex, int widthFactor, int heightFactor)
{
    renderTile(x, y, tileIndex, widthFactor, heightFactor, false);
}


void LTexture::renderTile(int x, int y, int tileIndex, int widthFactor, int heightFactor, bool mirror)
{
    renderTile(x, y, tileIndex, widthFactor, heightFactor, mirror, 0);

}

void LTexture::renderTile(int x, int y, int tileIndex, int widthFactor, int heightFactor, bool mirror, double rotation)
{
    SDL_Rect renderQuad = { x, y, 32 * widthFactor, 32 * heightFactor };
    SDL_Rect tileRect = { ((tileIndex * widthFactor) % 16) * 32, ((tileIndex * heightFactor) / 16) * 32, 32 * widthFactor, 32 * heightFactor };
    if (mirror)
        
        SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopyEx(GraphicsEngine::getActiveRenderer(), mTexture, &tileRect, &renderQuad, rotation, NULL, SDL_FLIP_NONE);
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

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}