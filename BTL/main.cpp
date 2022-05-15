#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>

#include "init.h"
#include "close.h"
#include "LTexture.h"
#include "Menu.h"
#include "Constant.h"
#include "Play.h"
using namespace std;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;

LTexture Bg;
LTexture *gTextTexture = new LTexture[5];
LTexture *gTextTexture_2 = new LTexture[15];
int check_background = 1, n = 0;
string *s = new string[15];

int main(int argc, char *args[])
{
    cout << "ditmemay";
    //init(gWindow, gRenderer, Width, Height);

    /*freopen("Result.txt", "r", stdin);
    cin >> n;
    getline(cin, s[0]);
    for (int i = 1; i <= 10; ++ i)
        getline(cin, s[i]);*/
    //xuly(gWindow, gRenderer, gFont);
    //Menu(check_background, gRenderer, gTextTexture, gTextTexture_2, s, Bg, gWindow, gFont);


    close(gWindow, gRenderer, gFont);
    return 0;
}
