#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>

#include "Constant.h"
#include "init.h"
#include "LTexture.h"
#include "Object.h"
#include "MyBullet.h"
#include "MyPlane.h"
#include "EnemyBullet.h"
#include "EnemyPlane.h"
#include "EnemyPlane2.h"
#include "HP.h"
#include "BigBang.h"
#include "Compare.h"
#include "CheckCollision.h"

using namespace std;

// Global variable

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
TTF_Font *pFont = NULL;
LTexture BG1;
LTexture BG2;
LTexture Fl;
LTexture Bullet;
LTexture EPlane;
LTexture EPlane2;
LTexture BB;
LTexture hp;
LTexture Point;
LTexture Time;
LTexture PressP;
LTexture PressB;

MyPlane Plane;
vector <HP> HPBox;
vector <Enemy> EnemyPlane;
vector <Enemy2> EnemyPlane2;
vector <BigBang> Explosions;
Uint32 timing = 0;
int score;
Uint32 realTime = 0;
Uint32 pauseTime = 0;
Uint32 continueTime = 0;

//Random EnemyPlane

void sinh(int sl1, int sl2)
{
    int x1 = min1 + rand() % (max1 - min1);
    if (x1 == 5 && EnemyPlane.size() < min(sl1, 5))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane_w);
            bool ok = true;
            for (int i = 0; i < EnemyPlane.size(); i++)
                if (EnemyPlane[i].alive1() == true)
                {
                    int a = EnemyPlane[i].x;
                    int b = Plane_w;
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            for (int i = 0; i < EnemyPlane2.size(); i++)
                if (EnemyPlane2[i].alive1() == true)
                {
                    int a = EnemyPlane2[i].x;
                    int b = Plane2_w;
                    int c = Plane_w;
                    if (y >= a - c && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy tam(gRenderer, y, 0, realTime);
        EnemyPlane.push_back(tam);
    }

    int x2 = min1 + rand() % (max1 - min1);
    if (x2 == 10 && EnemyPlane2.size() < min(sl2, 3))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane2_w);
            bool ok = true;
            for (int i = 0; i < EnemyPlane.size(); i++)
                if (EnemyPlane[i].alive1() == true)
                {
                    int a = EnemyPlane[i].x;
                    int b = Plane_w;
                    int c = Plane2_w;
                    if (y >= a - c && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            for (int i = 0; i < EnemyPlane2.size(); i++)
                if (EnemyPlane2[i].alive1() == true)
                {
                    int a = EnemyPlane2[i].x;
                    int b = Plane2_w;
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy2 tam(gRenderer, y, 0, realTime);
        EnemyPlane2.push_back(tam);
    }
}

//Update Objects

void update()
{
    //May bay minh va cham may bay dich

    vector <SDL_Rect> tam1 = Plane.getRect();
    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            vector <SDL_Rect> tam2 = EnemyPlane[i].getRect();
            for (int j = 0; j < tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= 30;
                        EnemyPlane[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    for (int i = 0; i < EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
            vector <SDL_Rect> tam2 = EnemyPlane2[i].getRect();
            for (int j = 0; j < tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= 50;
                        EnemyPlane2[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    //May bay dich va cham may bay dich

    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = i + 1; j < EnemyPlane.size(); j++)
                if (EnemyPlane[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane[j].x, EnemyPlane[j].y, EnemyPlane[j].w, EnemyPlane[j].h};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane[i].vx = -EnemyPlane[i].vx;
                        EnemyPlane[j].vx = -EnemyPlane[j].vx;
                    }
                }
        }

    for (int i = 0; i < EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
 //           SDL_Rect tam2 = {EnemyPlane2[i].x, EnemyPlane2[i].y, EnemyPlane2[i].w, EnemyPlane2[i].h};
            SDL_Rect tam2 = {EnemyPlane2[i].x, EnemyPlane2[i].y - EnemyPlane2[i].status.getHeight(), EnemyPlane2[i].w, EnemyPlane2[i].h + EnemyPlane2[i].status.getHeight()};
            for (int j = i + 1; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
//                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y - EnemyPlane2[j].status.getHeight(), EnemyPlane2[j].w, EnemyPlane2[j].h + EnemyPlane2[j].status.getHeight()};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane2[i].vx = -EnemyPlane2[i].vx;
                        EnemyPlane2[j].vx = -EnemyPlane2[j].vx;
                    }
                }
        }

    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = 0; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y - EnemyPlane2[j].status.getHeight(), EnemyPlane2[j].w, EnemyPlane2[j].h + EnemyPlane2[j].status.getHeight()};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane[i].vx = -EnemyPlane[i].vx;
                        EnemyPlane2[j].vx = -EnemyPlane2[j].vx;
                    }
                }
        }

    //Dan va cham may bay dich

    int i = 0;

    while (i < Plane.bullet.size())
    {
        SDL_Rect tam2 = Plane.bullet[i].getRect();
        bool ok = true;
        for (int j = 0; j < EnemyPlane.size(); j++)
            if (EnemyPlane[j].alive1() == true)
            {
                vector <SDL_Rect> tam3 = EnemyPlane[j].getRect();
                for (int k = 0; k < tam3.size(); k++)
                    if (CheckCollision(tam2, tam3[k]) == true)
                    {
                        EnemyPlane[j].hp -= 10;
                        Plane.bullet.erase(Plane.bullet.begin() + i);
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        if (ok == true)
        {
            for (int j = 0; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    vector <SDL_Rect> tam3 = EnemyPlane2[j].getRect();
                    for (int k = 0; k < tam3.size(); k++)
                        if (CheckCollision(tam2, tam3[k]) == true)
                        {
                            EnemyPlane2[j].hp -= 10;
                            Plane.bullet.erase(Plane.bullet.begin() + i);
                            ok = false;
                            break;
                        }
                    if (ok == false) break;
                }
        }
        if (ok == true) i++;
    }

    //Dan va cham may bay dong minh

    for (int j = 0; j < EnemyPlane.size(); j++)
    {
        int k = 0;
        while (k < EnemyPlane[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane[j].bullet[k].getRect();
            for (int e = 0; e < tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= 10;
                    EnemyPlane[j].bullet.erase(EnemyPlane[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    for (int j = 0; j < EnemyPlane2.size(); j++)
    {
        int k = 0;
        while (k < EnemyPlane2[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane2[j].bullet[k].getRect();
            for (int e = 0; e < tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= 10;
                    EnemyPlane2[j].bullet.erase(EnemyPlane2[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    //Xu li HP
    i = 0;
    while (i < HPBox.size())
    {
        bool ok = true;
        SDL_Rect tam2 = {HPBox[i].x, HPBox[i].y, HPBox[i].w, HPBox[i].h};
        SDL_Rect tam3 = {Plane.x, Plane.y, Plane.w, Plane.h};
        if (CheckCollision(tam2, tam3) == true)
        {
            Plane.hp += 20;
            HPBox.erase(HPBox.begin() + i);
            ok = false;
        }
        if (ok == true) i++;
    }

    //Cac vu no

    if (Plane.alive1() == true)
    {
        if (Plane.hp <= 0)
        {
            Plane.alive = false;
            BigBang k(gRenderer, Plane.x, Plane.y);
            Explosions.push_back(k);
        }
    }

    for (int j = 0; j < EnemyPlane.size(); j++)
        if (EnemyPlane[j].alive1() == true)
        {
            if (EnemyPlane[j].hp <= 0)
            {
                EnemyPlane[j].alive = false;
                score += 30;
                BigBang k(gRenderer, EnemyPlane[j].x, EnemyPlane[j].y);
                Explosions.push_back(k);
                int t1 = rand() % 15;
                if (t1 == 10)
                {
                    HP t2(gRenderer, EnemyPlane[j].x, EnemyPlane[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
    for (int j = 0; j < EnemyPlane2.size(); j++)
        if (EnemyPlane2[j].alive1() == true)
        {
            if (EnemyPlane2[j].hp <= 0)
            {
                EnemyPlane2[j].alive = false;
                score += 50;
                BigBang k(gRenderer, EnemyPlane2[j].x, EnemyPlane2[j].y);
                Explosions.push_back(k);
                int t1 = rand() % 15;
                if (t1 == 10)
                {
                    HP t2(gRenderer, EnemyPlane2[j].x, EnemyPlane2[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
}

//Explosions

void Exp()
{
    int i = 0;
    while (i < Explosions.size())
    {
        if (Explosions[i].render(gRenderer, BB) == false) Explosions.erase(Explosions.begin() + i);
        else i++;
    }
}

//Loadmedia

void loadmedia()
{
    gFont = TTF_OpenFont("VAPTIMN.TTF", 13);
    pFont = TTF_OpenFont("VAVOBI.TTF", 20);
    BG1.loadfromfile(gRenderer, "Jungle.png");
    BG2.loadfromfile(gRenderer, "Jungle.png");
    Fl.loadfromfile(gRenderer, "FinishLine3.png");
    Plane.loadfromfile(gRenderer, "MyPlane4.png");
    Bullet.loadfromfile(gRenderer, "Bullet3.png");
    EPlane.loadfromfile(gRenderer, "EnemyPlane4.png");
    EPlane2.loadfromfile(gRenderer, "EnemyPlane22.png");
    BB.loadfromfile(gRenderer, "Explosion3.png");
    hp.loadfromfile(gRenderer, "HP3.png");
    PressP.loadfromrenderedtext(gRenderer, pFont, "Press P to Continue", Color);
    PressB.loadfromrenderedtext(gRenderer, pFont, "Press B to Back to Menu", Color);
}

//Close

void close()
{
    BG1.close();
    BG2.close();
    Fl.close();
    Bullet.close();
    EPlane.close();
    EPlane2.close();
    BB.close();
    hp.close();
    Point.close();
    Time.close();
    PressB.close();
    PressP.close();
    Plane.close();
    for (int i = 0; i < EnemyPlane.size(); i++)
        EnemyPlane[i].close();
    for (int i = 0; i < EnemyPlane2.size(); i++)
        EnemyPlane2[i].close();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);
    TTF_CloseFont(pFont);

    gFont = NULL;
    pFont = NULL;
    gRenderer = NULL;
    gWindow = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

int main(int argc, char *args[])
{
    init(gWindow, gRenderer, Width, Height);
    loadmedia();
    score = 0;
    bool quit = false;
    bool fn = false;
    bool paused = false;
    SDL_Event e;
    SDL_Rect background = {0, Level_Height - Height, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    while (!quit)
    {
        Uint32 tam1 = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
            {
                if (paused == true)
                {
                    continueTime = SDL_GetTicks();
                    paused = false;
                }
                else
                {
                    pauseTime = realTime;
                    paused = true;
                }
            }
            else if (Plane.alive1() == true) Plane.handle(gRenderer, e);
        }

        if (background.y < 0)
        {
            SDL_Rect background2 = {0, Fl.getHeight() + background.y, Width, abs(background.y)};
            SDL_Rect background3 = {0, 0, Width, Height - abs(background.y)};
            Fl.render(gRenderer, 0, 0, &background2);
            BG2.render(gRenderer, 0, abs(background.y), &background3);
            SDL_Rect tam1 = {0, 0, Width, abs(background.y)};
            SDL_Rect tam2 = Plane.getPos();
            if (fn == false && CheckCollision(tam1, tam2) == true)
            {
                score += 100;
                fn = true;
            }
        }
        else
        {
            if (background.y <= Level_Height - Height)
            {
                fn = false;
                BG1.render(gRenderer, 0, 0, &background);
            }
            else
            {
                int tam = Level_Height - background.y;
                SDL_Rect background2 = {0, background.y, Width, tam};
                SDL_Rect background3 = {0, 0, Width, Fl.getHeight()};
                SDL_Rect background4 = {0, 0, Width, Height - tam - Fl.getHeight()};
                BG1.render(gRenderer, 0, 0, &background2);
                Fl.render(gRenderer, 0, tam, &background3);
                BG2.render(gRenderer, 0, tam + Fl.getHeight(), &background4);
                SDL_Rect tam1 = {0, tam, Width, Fl.getHeight()};
                SDL_Rect tam2 = Plane.getPos();
                if (fn == false && CheckCollision(tam1, tam2) == true)
                {
                    score += 100;
                    fn = true;
                }
            }
        }
        if (Plane.alive1() == true)
        {
            if (paused == false)
            {
                stringstream ss;
                ss << "Score: " << score;
                Point.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);
                ss.str("");
                realTime = pauseTime + SDL_GetTicks() - continueTime;
                Uint32 tg = realTime / 1000;
                Uint32 m = tg / 60;
                Uint32 s = tg - m * 60;
                Uint32 ms = (realTime - tg * 1000) * 60 / 1000;
                ss << "Time: " << m << ":" << s << ":" << ms;
                Time.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);

                background.y -= 1;
                if (background.y < -Fl.getHeight()) background.y = Level_Height;
                update();
                sinh(2 + realTime / 30000, 1 + realTime / 60000);

                Plane.move1();
                int i = 0;
                while (i < EnemyPlane.size())
                {
                    if (EnemyPlane[i].move1(gRenderer, realTime) == false) EnemyPlane.erase(EnemyPlane.begin() + i);
                    else i++;
                }
                i = 0;
                while (i < EnemyPlane2.size())
                {
                    if (EnemyPlane2[i].move1(gRenderer, realTime) == false) EnemyPlane2.erase(EnemyPlane2.begin() + i);
                    else i++;
                }
                i = 0;
                while (i < HPBox.size())
                {
                    if (HPBox[i].move1() == false) HPBox.erase(HPBox.begin() + i);
                    else i++;
                }
            }
            Point.render(gRenderer, 0, 0);
            Time.render(gRenderer, 0, Point.getHeight());
            Plane.render(gRenderer, gFont, Bullet);
            for (int i = 0; i < EnemyPlane.size(); i++)
                EnemyPlane[i].render(gRenderer, gFont, EPlane, Bullet);
            for (int i = 0; i < EnemyPlane2.size(); i++)
                EnemyPlane2[i].render(gRenderer, gFont, EPlane2, Bullet);
            for (int i = 0; i < HPBox.size(); i++)
                HPBox[i].render(gRenderer, hp);
            if (paused == true)
            {
                PressP.render(gRenderer, (Width - PressP.getWidth()) / 2, (Height - PressP.getHeight()) / 2);
                PressB.render(gRenderer, (Width - PressB.getWidth()) / 2, (Height - PressP.getHeight()) / 2 + PressB.getHeight());
            }
        }

        if (tam1 / 10 > timing)
        {
            Exp();
            timing = tam1 / (10);
        }
        SDL_RenderPresent(gRenderer);

        Uint32 tam2 = SDL_GetTicks() - tam1;
        if (tam2 < FPS) SDL_Delay(FPS - tam2);
    }
    close();
    return 0;
}
