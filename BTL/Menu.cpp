#include <iostream>

#include "Menu.h"

bool loadMedia_1(int check_background, SDL_Renderer *&gRenderer, LTexture &Bg)
{
	if (check_background == 1) Bg.loadfromfile(gRenderer, "zz.png" );
    if (check_background == 2) Bg.loadfromfile(gRenderer, "z2.png" );
    if (check_background == 3) Bg.loadfromfile(gRenderer, "z3.png" );
}

bool loadMedia_2(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture)
{
    TTF_Font *gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
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
	TTF_Font *gFont = TTF_OpenFont( "lazy.ttf", fsize);
	TTF_Font *gFont1 = TTF_OpenFont( "lazy.ttf", fsize1);
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {55, 155, 0};
    if (x == 1) gTextTexture_2[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor2);
    else gTextTexture_2[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor3);

    for (int i = 1; i <= 10; ++ i) {
        if (x == i + 1) gTextTexture_2[i].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor2);
        else gTextTexture_2[i].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor);
    }

    if (x == 12) gTextTexture_2[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else gTextTexture_2[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor3);

}
/*bool loadMedia_4(int fsize) {
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    int fsize1 = 0;
    if (fsize == 50) fsize1 = 30;
    else if (fsize == 30) fsize1 = 15;
    gTextTexture_1[0].loadFromRenderedText("wuyrwueruewrwehurwehruweruehruewhehwuwrsfdsdsfdsfdsfdsfdfdsfdsfdsfdsruwherwueh", textColor, gFont = TTF_OpenFont( "lazy.ttf", fsize ), gRenderer);
    gTextTexture_1[8].loadFromRenderedText("Nguyen Thanh Son && Hoang Minh Quang", textColor, gFont = TTF_OpenFont( "lazy.ttf", 30 ), gRenderer);
    gTextTexture_1[9].loadFromRenderedText("BACK", textColor2, gFont = TTF_OpenFont( "lazy.ttf", 70 ), gRenderer);
    return 1;
}
bool loadMedia_5() {
    if (check_mixer == 1) gMusic = Mix_LoadMUS( "ft.mp3" );
    if (check_mixer == 2) gMusic = Mix_LoadMUS( "h3.mp3" );
    if (check_mixer == 3) gMusic = Mix_LoadMUS( "h2.mp3" );
    return 1;
}
bool loadMedia_6(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_3[0].loadFromRenderedText( "RESOLUTION", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[0].loadFromRenderedText( "RESOLUTION", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_3[1].loadFromRenderedText( "BACKGROUND", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[1].loadFromRenderedText( "BACKGROUND", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_3[2].loadFromRenderedText( "MUSIC", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[2].loadFromRenderedText( "MUSIC", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_3[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_7(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_4[0].loadFromRenderedText( "AUTO-RESOLUTION", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[0].loadFromRenderedText( "AUTO-RESOLUTION", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_4[1].loadFromRenderedText( "640 * 320", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[1].loadFromRenderedText( "640 * 320", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_4[2].loadFromRenderedText( "FULLSCREEN", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[2].loadFromRenderedText( "FULLSCREEN", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_4[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_8(int x) {
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_5[0].loadFromRenderedText( "YES", textColor2, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    else gTextTexture_5[0].loadFromRenderedText( "YES", textColor, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    if (x == 2) gTextTexture_5[1].loadFromRenderedText( "NO", textColor2, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    else gTextTexture_5[1].loadFromRenderedText( "NO", textColor, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    return 1;
}
bool loadMedia_9(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) gTextTexture_6[2].loadFromRenderedText( "STARWAR", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[2].loadFromRenderedText( "STARWAR", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_6[1].loadFromRenderedText( "FARMLAND", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[1].loadFromRenderedText( "FARMLAND", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 1) gTextTexture_6[0].loadFromRenderedText( "AUTO-SCREEN", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[0].loadFromRenderedText( "AUTO-SCREEN", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_6[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_10(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_7[0].loadFromRenderedText( "AUTO-MUSIC", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[0].loadFromRenderedText( "AUTO-MUSIC", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_7[1].loadFromRenderedText( "HHH", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[1].loadFromRenderedText( "HHH", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_7[2].loadFromRenderedText( "ZZZ", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[2].loadFromRenderedText( "ZZZ", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_7[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
}*/



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
/*int Update_3(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 4;
    if (keyrow == 1 && x == -1) return 4;
    if (keyrow == 4 && x == 1) return 1;
    return keyrow + x;
}
int Update_4(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 2;
    if (keyrow == 1 && x == -1) return 2;
    if (keyrow == 2 && x == 1) return 1;
    return keyrow + x;
}
*/

