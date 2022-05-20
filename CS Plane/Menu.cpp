#include <iostream>

#include "Menu.h"

bool loadMedia_1(SDL_Renderer *&gRenderer, LTexture &Bg)
{
	Bg.loadfromfile(gRenderer, "homebg1.jpg" );
}

bool loadMedia_2(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture)
{
    TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize );
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture[0].loadfromrenderedtext(gRenderer, gFont, "PLAY", textColor2);
    else gTextTexture[0].loadfromrenderedtext(gRenderer, gFont, "PLAY", textColor);
    if (x == 2) gTextTexture[1].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor2);
    else gTextTexture[1].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor);
    if (x == 3) gTextTexture[2].loadfromrenderedtext(gRenderer, gFont, "SETTING", textColor2);
    else gTextTexture[2].loadfromrenderedtext(gRenderer, gFont, "SETTING", textColor);
    if (x == 4) gTextTexture[3].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor2);
    else gTextTexture[3].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor);
    if (x == 5) gTextTexture[4].loadfromrenderedtext(gRenderer, gFont, "EXIT", textColor2);
    else gTextTexture[4].loadfromrenderedtext(gRenderer, gFont, "EXIT", textColor);
}

bool loadMedia_3(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_2, string *&s)
{
	int fsize1 = 0;
    if (fsize == 50) fsize1 = 30;
    else fsize1 = 25;
	TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize);
	TTF_Font *gFont1 = TTF_OpenFont( "VAVOI.TTF", fsize1);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {55, 155, 0};
    if (x == 1) gTextTexture_2[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor2);
    else gTextTexture_2[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor3);

    for (int i = 0; i < 10; ++ i) {
        if (x == i + 2) gTextTexture_2[i + 1].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor2);
        else gTextTexture_2[i + 1].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor);
    }

    if (x == 12) gTextTexture_2[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_2[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor3);

}
bool loadMedia_4(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_3) {
    int fsize1 = 0;
    if (fsize == 50) fsize1 = 30;
    else fsize1 = 25;
	TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize);
	TTF_Font *gFont1 = TTF_OpenFont( "VAVOI.TTF", 20);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {55, 155, 0};
    if (x == 1) gTextTexture_3[0].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor2);
    else gTextTexture_3[0].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor3);
    gTextTexture_3[1].loadfromrenderedtext(gRenderer, gFont, "MOVE UP: UP", textColor);
    gTextTexture_3[2].loadfromrenderedtext(gRenderer, gFont, "MOVE DOWN: DOWN", textColor);
    gTextTexture_3[3].loadfromrenderedtext(gRenderer, gFont, "MOVE LEFT: LEFT", textColor);
    gTextTexture_3[4].loadfromrenderedtext(gRenderer, gFont, "MOVE RIGHT: RIGHT", textColor);
    gTextTexture_3[5].loadfromrenderedtext(gRenderer, gFont, "SHOOT: SPACE", textColor);
    gTextTexture_3[8].loadfromrenderedtext(gRenderer, gFont, "EXIT: E", textColor);
    gTextTexture_3[7].loadfromrenderedtext(gRenderer, gFont, "BACK: B", textColor);
    gTextTexture_3[6].loadfromrenderedtext(gRenderer, gFont, "PAUSE: P", textColor);
    gTextTexture_3[9].loadfromrenderedtext(gRenderer, gFont1, "MADE BY SON AND QUANG", textColor);
    if (x == 2) gTextTexture_3[10].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_3[10].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor3);
}
bool loadMedia_5(int &check_mixer, Mix_Music *&gMusic)
{
    if (check_mixer == 1) gMusic = Mix_LoadMUS( "ft.mp3" );
    if (check_mixer == 2) gMusic = Mix_LoadMUS( "h2.mp3" );
    if (check_mixer == 3) gMusic = Mix_LoadMUS( "h3.mp3" );
}
bool loadMedia_6(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_4) {
    TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};

    if (x == 1) gTextTexture_4[0].loadfromrenderedtext(gRenderer, gFont, "BACKGROUND", textColor2);
    else gTextTexture_4[0].loadfromrenderedtext(gRenderer, gFont, "BACKGROUND", textColor);
    if (x == 2) gTextTexture_4[1].loadfromrenderedtext(gRenderer, gFont, "MUSIC", textColor2);
    else gTextTexture_4[1].loadfromrenderedtext(gRenderer, gFont, "MUSIC", textColor);
    if (x == 3) gTextTexture_4[2].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_4[2].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}

bool loadMedia_8(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_6) {
    TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) gTextTexture_6[2].loadfromrenderedtext(gRenderer, gFont, "2", textColor2);
    else gTextTexture_6[2].loadfromrenderedtext(gRenderer, gFont, "2", textColor);
    if (x == 2) gTextTexture_6[1].loadfromrenderedtext(gRenderer, gFont, "1", textColor2);
    else gTextTexture_6[1].loadfromrenderedtext(gRenderer, gFont, "1", textColor);
    if (x == 1) gTextTexture_6[0].loadfromrenderedtext(gRenderer, gFont, "JUNGLE", textColor2);
    else gTextTexture_6[0].loadfromrenderedtext(gRenderer, gFont, "JUNGLE", textColor);
    if (x == 4) gTextTexture_6[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_6[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}
bool loadMedia_9(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_7) {
    TTF_Font *gFont = TTF_OpenFont( "VGOUDYB.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) gTextTexture_7[2].loadfromrenderedtext(gRenderer, gFont, "2", textColor2);
    else gTextTexture_7[2].loadfromrenderedtext(gRenderer, gFont, "2", textColor);
    if (x == 2) gTextTexture_7[1].loadfromrenderedtext(gRenderer, gFont, "1", textColor2);
    else gTextTexture_7[1].loadfromrenderedtext(gRenderer, gFont, "1", textColor);
    if (x == 1) gTextTexture_7[0].loadfromrenderedtext(gRenderer, gFont, "0", textColor2);
    else gTextTexture_7[0].loadfromrenderedtext(gRenderer, gFont, "0", textColor);
    if (x == 4) gTextTexture_7[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_7[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}

int Update(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 5;
    if (keyrow == 1 && x == -1) return 5;
    if (keyrow == 5 && x == 1) return 1;
    return keyrow + x;
}
int Update_2(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 12;
    if (keyrow == 1 && x == -1) return 12;
    if (keyrow == 12 && x == 1) return 1;
    return keyrow + x;
}
int Update_3(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 3;
    if (keyrow == 1 && x == -1) return 3;
    if (keyrow == 3 && x == 1) return 1;
    return keyrow + x;
}
int Update_4(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 2;
    if (keyrow == 1 && x == -1) return 2;
    if (keyrow == 2 && x == 1) return 1;
    return keyrow + x;
}
int Update_5(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 4;
    if (keyrow == 1 && x == -1) return 4;
    if (keyrow == 4 && x == 1) return 1;
    return keyrow + x;
}
