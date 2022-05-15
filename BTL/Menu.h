#ifndef Menu_h
#define Menu_h

#include "LTexture.h"
#include "init.h"
#include "close.h"
#include "Play.h"

bool loadMedia_1(int check_background, SDL_Renderer *&gRenderer, LTexture &Bg);
bool loadMedia_2(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture);
bool loadMedia_3(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_2, string *&s);
bool loadMedia_4();
bool loadMedia_5();
bool loadMedia_6();
bool loadMedia_7();
bool loadMedia_8();
bool loadMedia_9();
bool loadMedia_10();


int Update(int keyrow, int x);
int Update_2(int keyrow, int x);
int Update_3();
int Update_4();

void Solution();
void Leaderboard(int &check_background, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_2, LTexture Bg, string *&s);
void Tutorial();
void Menu(int &check_background, SDL_Renderer *&gRenderer, LTexture *&gTextTexture, LTexture *&gTextTexture_2, string *&s, LTexture Bg, SDL_Window *gWindow, TTF_Font *gFont);

void S_resolution();
void S_background();
void S_music();
void Accept();

#endif
