#include <iostream>

#include "Play.h"

// Global variable

LTexture BG;
MyPlane Plane;
vector <HP> HPBox;
vector <Enemy> EnemyPlane;
vector <Enemy2> EnemyPlane2;
vector <BigBang> Explosions;
Uint32 timing = 0;


//Random EnemyPlane
void sinh(SDL_Renderer *&gRenderer)
{
    int x1 = min1 + rand() % (max1 - min1);
    if (x1 == 5 && EnemyPlane.size() < 3)
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
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy tam(gRenderer, y, 0);
        EnemyPlane.push_back(tam);
    }

    int x2 = min1 + rand() % (max1 - min1);
    if (x2 == 10 && EnemyPlane2.size() < 1)
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
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy2 tam(gRenderer, y, 0);
        EnemyPlane2.push_back(tam);
    }
}

//Update Objects

void update(SDL_Renderer *&gRenderer)
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
            SDL_Rect tam2 = {EnemyPlane2[i].x, EnemyPlane2[i].y, EnemyPlane2[i].w, EnemyPlane2[i].h};
            for (int j = i + 1; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
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
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
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

void Exp(SDL_Renderer *&gRenderer)
{
    int i = 0;
    while (i < Explosions.size())
    {
        if (Explosions[i].render(gRenderer) == false) Explosions.erase(Explosions.begin() + i);
        else i++;
    }
}

//Loadmedia
void loadmedia(SDL_Renderer *&gRenderer, TTF_Font *&gFont)
{
    gFont = TTF_OpenFont("VAPTIMN.TTF", 13);
    BG.loadfromfile(gRenderer, "Jungle.png");
    Plane.loadfromfile(gRenderer, "MyPlane4.png");
}

void xuly(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont)
{

    loadmedia(gRenderer, gFont);
    bool quit = false;
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
            if (Plane.alive1() == true) Plane.handle(gRenderer, e);
        }

        BG.render(gRenderer, 0, 0, &background);
        if (Plane.alive1() == true)
        {
            background.y -= 1;
            if (background.y < 0) background.y = Level_Height - Height;

            update(gRenderer);
            sinh(gRenderer);

            Plane.move1();
            int i = 0;
            while (i < EnemyPlane.size())
            {
                if (EnemyPlane[i].move1(gRenderer) == false) EnemyPlane.erase(EnemyPlane.begin() + i);
                else i++;
            }
            i = 0;
            while (i < EnemyPlane2.size())
            {
                if (EnemyPlane2[i].move1(gRenderer) == false) EnemyPlane2.erase(EnemyPlane2.begin() + i);
                else i++;
            }
            i = 0;
            while (i < HPBox.size())
            {
                if (HPBox[i].move1() == false) HPBox.erase(HPBox.begin() + i);
                else i++;
            }

            Plane.render(gRenderer, gFont);
            for (int i = 0; i < EnemyPlane.size(); i++)
                EnemyPlane[i].render(gRenderer, gFont);
            for (int i = 0; i < EnemyPlane2.size(); i++)
                EnemyPlane2[i].render(gRenderer, gFont);
            for (int i = 0; i < HPBox.size(); i++)
                HPBox[i].render(gRenderer);
        }

        if (tam1 / 10 > timing)
        {
            Exp(gRenderer);
            timing = tam1 / (10);
        }
        SDL_RenderPresent(gRenderer);

        Uint32 tam2 = SDL_GetTicks() - tam1;
        if (tam2 < FPS) SDL_Delay(FPS - tam2);
    }

}
