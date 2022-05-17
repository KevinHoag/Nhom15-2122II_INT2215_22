#include <iostream>
#include "init.h"

void close(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, Mix_Music *&gMusic)
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    Mix_FreeMusic( gMusic );
    SDL_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    gRenderer = NULL;
    gWindow = NULL;
    gMusic = NULL;
}
