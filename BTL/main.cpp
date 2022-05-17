#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


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
TTF_Font *pFont = NULL;
Mix_Music *gMusic = NULL;

LTexture Bg;
vector<pair<int, int> > res;
int check_background = 1, check_mixer = 1, n = 0;
string *s = new string[15];

int main(int argc, char *args[])
{

    init(gWindow, gRenderer, Width, Height);

//    freopen("Result.txt", "r", stdin);
//    cin >> n;
//    getline(cin, s[0]);
//    for (int i = 0; i < n; ++ i)
//        getline(cin, s[i]);
//    for (int i = 1; i <= n; ++ i) {
//            int score = 0, time = 0;
//            cin >> score >> time;
//            res.push_back({score, time});
//    }
//    freopen("Result.txt", "w", stdout);
    Menu(check_mixer, check_background, gRenderer, s, Bg, gWindow, gFont, pFont, gMusic, res);
//    sort(res.begin(), res.end());
//    cout << n << '\n';
//    for (int i = 0; i < 10; ++ i) {
//        stringstream ss;
//        ss << "PLAYER " << i + 1 << " : SCORE : " << res[res.size() - i - 1].first << " : TIME : " <<  res[res.size() - i - 1].second;
//        cout << ss.str() << '\n';
//    }
//    for (int i = res.size() - 1; i > res.size() - 10; -- i) cout << res[i].first << ' ' << res[i].second << '\n';
    close(gWindow, gRenderer, gFont, gMusic);
    return 0;
}
