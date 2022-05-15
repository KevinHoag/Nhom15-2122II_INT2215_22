#include <iostream>

#include "Menu.h"

void Menu(int &check_background, SDL_Renderer *&gRenderer, LTexture *&gTextTexture, LTexture *&gTextTexture_2, string *&s, LTexture Bg, SDL_Window *gWindow, TTF_Font *gFont) {
    bool quit = false; int next = 0, keyrow = 0;
    SDL_Event e;
    loadMedia_1(check_background, gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0; h = 100, w = 100, sum = 50, fsize = 50;

        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update(keyrow, 1);
                   break;
                   case SDLK_e:
                       exit(0);
                   break;
                   case SDLK_b:
                       keyrow = 0;
                   break;
                   case SDLK_RETURN:
                        next = 1;
                   break;
            }
        if (next == 1) {
            if (keyrow == 0) next = 0;
            else if (keyrow == 1) {
                    next = 0;
                    close(gWindow, gRenderer, gFont);
                    init(gWindow, gRenderer, Width, Height);
                    xuly(gWindow, gRenderer, gFont);
                 }
            else if (keyrow == 2) {
                    next = 0;
                    close(gWindow, gRenderer, gFont);
                    init(gWindow, gRenderer, Width, Height);
                    Leaderboard(check_background, gRenderer, gTextTexture_2, Bg, s);
                 }
            else if (keyrow == 3) {
                    next = 0;
                    //Setting();
                    //close();
                    //Solution();
                 }
            else if (keyrow == 4) {
                    //Tutorial();
                    next = 0;
                 }
            else if (keyrow == 5) {
                    exit(0);
                 }
            continue;
        }

        Bg.render(gRenderer, 0, 0, &background);
        loadMedia_2(keyrow, fsize, gRenderer, gTextTexture);
        for (int i = 0; i < 5; ++ i) {
            gTextTexture[i].render(gRenderer, h, w );
            w += sum;
        }
        SDL_RenderPresent( gRenderer );
    }
}

void Leaderboard(int &check_background, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_2, LTexture Bg, string *&s) {
    bool quit = false; int next = 0, keyrow = 0;
    SDL_Event e;
    loadMedia_1(check_background, gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0; h = 50, w = 20, sum = 40, fsize = 40;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update_2(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update_2(keyrow, 1);
                   break;
                   case SDLK_b:
                       quit = 1;
                   break;
                   case SDLK_RETURN:
                       next = 1;
                   break;
            }
        if (next) {
            if (keyrow == 12) quit = 1;
            next = 0;
            continue;
        }
        Bg.render(gRenderer, 0, 0, &background);
        loadMedia_3(keyrow, fsize, gRenderer, gTextTexture_2, s);
        for (int i = 0; i < 12; ++ i) {
            gTextTexture_2[i].render(gRenderer, h, w );
            w += sum;
        }
        SDL_RenderPresent( gRenderer );
    }
    //close(gWindow, gRenderer, gFont);
}
