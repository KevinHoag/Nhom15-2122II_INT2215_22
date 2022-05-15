#include <iostream>
#include "init.h"

void close(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont)
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    IMG_Quit();
    gRenderer = NULL;
    gWindow = NULL;
}
