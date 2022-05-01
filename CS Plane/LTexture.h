#include "init.h"

class LTexture
{
    int w;
    int h;
    SDL_Texture *mTexture;
public:
    LTexture();
    void loadfromfile(string path);
    void render(int x, int y, SDL_Rect *p = NULL);
    int getWidth();
    int getHeight();
    void close();
};

LTexture::LTexture()
{
    w = 0;
    h = 0;
    mTexture = NULL;
}

void LTexture::loadfromfile(string path)
{
    SDL_Surface *gSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(gSurface, SDL_TRUE, (gSurface->format, 0, 0, 0));
    if (!gSurface)
    {
        cout << "IMG_Load failed: " << SDL_GetError() << endl;
        return;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (!mTexture) cout << "CreateTextureFromSurface failed: " << SDL_GetError() << endl;
    w = gSurface->w;
    h = gSurface->h;
    SDL_FreeSurface(gSurface);
    gSurface = NULL;
}

void LTexture::render(int x, int y, SDL_Rect *p)
{
    SDL_Rect tam = {x, y, w, h};
    if (p != NULL)
    {
        tam.w = p->w;
        tam.h = p->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, p, &tam);
}

int LTexture::getHeight()
{
    return h;
}

int LTexture::getWidth()
{
    return w;
}

void LTexture::close()
{
    w = 0;
    h = 0;
    mTexture = NULL;
}

