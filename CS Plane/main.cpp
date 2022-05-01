#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "Object.h"
#include "BigBang.h"
#include "Compare.h"

using namespace std;

const int Level_Height = 4023;
const int Level_Width = 1024;
const int FPS = 1000 / 60;
const int Bullet_w = 6;
const int Bullet_h = 14;
const int Plane_w = 50;
const int Plane_h = 60;
const int Plane2_w = 85;
const int Plane2_h = 90;
const int max1 = 100;
const int min1 = 1;

class MyBullet: public Object
{
    SDL_Rect a;
public:
    MyBullet(int x_ = 0, int y_ = 0);
    void move1();
    bool render();
    SDL_Rect &getRect();
    void shift();
};

class MyPlane: public Object
{
    int vx = 0;
    int vy = 0;
    vector <MyBullet> bullet;
    vector <SDL_Rect> pos;
    bool alive;
public:
    int hp;
    void loadfromfile(string path);
    void handle(SDL_Event &e);
    void move1();
    void render();
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
};

class EnemyBullet: public Object
{
    SDL_Rect a;
public:
    EnemyBullet(int x_ = 0, int y_ = 0);
    bool move1();
    void render();
    void shift();
    SDL_Rect &getRect();
};

class Enemy: public Object
{
    int vx;
    bool alive;
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
public:
    int hp;
    Enemy(int x_ = 0, int y_ = 0);
    bool move1();
    void render();
    int getX();
    int getY();
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
};

class Enemy2: public Object
{
    int vx;
    int dem;
    bool alive = false;
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
public:
    int hp;
    Enemy2(int x_ = 0, int y_ = 0);
    bool move1();
    void render();
    int getX();
    int getY();
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
};

// Global variable

LTexture BG;
MyPlane Plane;
vector <Enemy> EnemyPlane;
vector <Enemy2> EnemyPlane2;
vector <BigBang> Explosions;
Uint32 timing = 0;

//Check collisions

bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    if (a.y > b.y + b.h) return false;
    if (a.y + a.h < b.y) return false;
    if (a.x > b.x + b.w) return false;
    if (a.x + a.w < b.x) return false;
    return true;
}

//MyBullet functions

MyBullet::MyBullet(int x_, int y_)
{
    img.loadfromfile("Bullet3.png");
    x = x_;
    y = y_;
    w = img.getWidth();
    h = img.getHeight();
    a = {x, y, w, h};
}

void MyBullet::move1()
{
    y -= vt / 2;
    shift();
}

bool MyBullet::render()
{
    if (y < 0)
    {
        return false;
    }
    Object::render();
    return true;
}

SDL_Rect &MyBullet::getRect()
{
    return a;
}

void MyBullet::shift()
{
    a.x = x;
    a.y = y;
}

//MyPlane functions

void MyPlane::loadfromfile(string path)
{
    img.loadfromfile(path.c_str());
    hp = 100;
    alive = true;
    w = img.getWidth();
    h = img.getHeight();
    x = (Width - w) / 2;
    y = Height - h;

    pos.resize(6);

    pos[0].x = 0;
    pos[0].y = 0;
    pos[0].w = w * 4 / 15;
    pos[0].h = h * 17 / 77;

    pos[1].x = 0;
    pos[1].y = 0;
    pos[1].w = w * 1 / 10;
    pos[1].h = h * 28 / 77;

    pos[2].x = 0;
    pos[2].y = 0;
    pos[2].w = w * 1 / 4;
    pos[2].h = h - h * 15 / 77;

    pos[3].x = 0;
    pos[3].y = 0;
    pos[3].w = w * 1 / 10;
    pos[3].h = h * 28 / 77;

    pos[4].x = 0;
    pos[4].y = 0;
    pos[4].w = w * 4 / 15;
    pos[4].h = h * 17 / 77;

    pos[5].x = 0;
    pos[5].y = 0;
    pos[5].w = w * 5 / 12;
    pos[5].h = h * 15 / 77;

    shift();
}

void MyPlane::handle(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            vy -= vt;
            break;
            case SDLK_DOWN:
            vy += vt;
            break;
            case SDLK_LEFT:
            vx -= vt;
            break;
            case SDLK_RIGHT:
            vx += vt;
            break;
            case SDLK_RETURN:
            MyBullet tam(x + (w - Bullet_w) / 2, y);
            bullet.push_back(tam);
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            vy += vt;
            break;
            case SDLK_DOWN:
            vy -= vt;
            break;
            case SDLK_LEFT:
            vx += vt;
            break;
            case SDLK_RIGHT:
            vx -= vt;
            break;
        }
    }
}

void MyPlane::move1()
{
    if (alive == true)
    {
        if (hp <= 0)
        {
            alive = false;
            BigBang k(x, y);
            Explosions.push_back(k);
        }
    }
    int i = 0;
    while (i < bullet.size())
    {
        bool ok = true;
        SDL_Rect a = bullet[i].getRect();

        for (int j = 0; j < EnemyPlane.size(); j++)
            if (EnemyPlane[j].hp > 0 && EnemyPlane[j].alive1() == true)
        {
            vector <SDL_Rect> b = EnemyPlane[j].getRect();
            for (int k = 0; k < b.size() - 1; k++)
                if (CheckCollision(a, b[k]) == true)
            {
                EnemyPlane[j].hp -= 10;
                ok = false;
                bullet.erase(bullet.begin() + i);
                break;
            }
            if (ok == false) break;
        }

        for (int j = 0; j < EnemyPlane2.size(); j++)
            if (EnemyPlane2[j].hp > 0 && EnemyPlane2[j].alive1() == true)
        {
            vector <SDL_Rect> b = EnemyPlane2[j].getRect();
            for (int k = 0; k < b.size(); k++)
                if (CheckCollision(a, b[k]) == true)
            {
                EnemyPlane2[j].hp -= 10;
                ok = false;
                bullet.erase(bullet.begin() + i);
                break;
            }
            if (ok == false) break;
        }

        if (ok == true)
        {
            bullet[i].move1();
            i++;
        }
    }
    if (alive == true)
    {
        x += vx;
        if (x < 0 || x + w > Width)  x -= vx;
        y += vy;
        if (y < 0 || y + h > Height) y -= vy;
        shift();
    }
}

void MyPlane::render()
{
    if (alive == true) Object::render();
    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].render() == false) bullet.erase(bullet.begin() + i);
        else i++;
    }
}

vector <SDL_Rect> MyPlane::getRect()
{
    return pos;
}

void MyPlane::shift()
{
    int r = x;
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i].x = r;
        pos[i].y = y + (h - pos[5].h - pos[i]. h);
        r += pos[i].w;
    }
    pos[5].x = x + (w - pos[5].w) / 2;
    pos[5].y = y + (h - (h - pos[5].h));
}

bool MyPlane::alive1()
{
    return alive;
}

//EnemyBullet functions

EnemyBullet::EnemyBullet(int x_, int y_)
{
    img.loadfromfile("Bullet3.png");
    x = x_;
    y = y_;
    w = img.getWidth();
    h = img.getHeight();
    a = {x, y, w, h};
}

bool EnemyBullet::move1()
{
    if (y > Height) return false;
    vector <SDL_Rect> tam = Plane.getRect();
    for (int i = 0; i < tam.size(); i++)
        if (Plane.hp > 0 && CheckCollision(tam[i], a) == true)
        {
            Plane.hp -= 10;
            return false;
        }
    y += vt / 3;
    shift();
    return true;
}

void EnemyBullet::render()
{
    Object::render();
}

void EnemyBullet::shift()
{
    a.x = x;
    a.y = y;
}

SDL_Rect &EnemyBullet::getRect()
{
    return a;
}

//Enemy functions

Enemy::Enemy(int x_, int y_)
{
    hp = 30;
    img.loadfromfile("EnemyPlane4.png");
    alive = true;
    w = img.getWidth();
    h = img.getHeight();
    x = x_;
    y = -h;
    vx = rand() % 2;

    pos.resize(6);

    pos[0].x = 0;
    pos[0].y = 0;
    pos[0].w = w * 4 / 15;
    pos[0].h = h * 17 / 77;

    pos[1].x = 0;
    pos[1].y = 0;
    pos[1].w = w * 1 / 10;
    pos[1].h = h * 28 / 77;

    pos[2].x = 0;
    pos[2].y = 0;
    pos[2].w = w * 1 / 4;
    pos[2].h = h - h * 15 / 77;

    pos[3].x = 0;
    pos[3].y = 0;
    pos[3].w = w * 1 / 10;
    pos[3].h = h * 28 / 77;

    pos[4].x = 0;
    pos[4].y = 0;
    pos[4].w = w * 4 / 15;
    pos[4].h = h * 17 / 77;

    pos[5].x = 0;
    pos[5].y = 0;
    pos[5].w = w * 5 / 12;
    pos[5].h = h * 15 / 77;

    shift();
}

bool Enemy::move1()
{
    if (y > Height) return false;
    if (alive == false && bullet.size() == 0) return false;
    if (alive == true)
    {
        if (hp <= 0) alive = false;
        else
        {
            vector <SDL_Rect> tam = Plane.getRect();
            bool ok = true;
            for (int i = 0; i < tam.size(); i++)
            {
                for (int j = 0; j < pos.size(); j++)
                    if (CheckCollision(tam[i], pos[j]) == true)
                    {
                        Plane.hp -= 30;
                        alive = false;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }
        if (alive == false)
        {
                BigBang k(x, y);
                Explosions.push_back(k);
        }
        if (y % 200 == 0)
        {
            EnemyBullet tam(x + (w - Bullet_w) / 2, y + h - Bullet_h / 2);
            bullet.push_back(tam);
        }
    }
    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].move1() == false) bullet.erase(bullet.begin() + i);
        else i++;
    }
    SDL_Rect tam1 = {x, y, w, h};
    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
    {
        SDL_Rect tam2 = {EnemyPlane[i].getX(), EnemyPlane[i].getY(), Plane_w, Plane_h};
        if (tam1 != tam2 && CheckCollision(tam1, tam2) == true) vx = -vx;
    }
    for (int i = 0; i < EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
    {
        SDL_Rect tam2 = {EnemyPlane2[i].getX(), EnemyPlane2[i].getY(), Plane2_w, Plane2_h};
        if (CheckCollision(tam1, tam2) == true) vx = -vx;
    }
    if (x + w > Width || x < 0) vx = -vx;
    y += 1;
    x += vx;
    shift();

    return true;
}

void Enemy::render()
{
    if (alive == true)
    {
        if (y <= 0)
        {
            SDL_Rect tam = {0, abs(y), w, h + y};
            img.render(x, 0, &tam);
        }
        else
        {
            Object::render();
        }
    }
    for (int i = 0;i < bullet.size(); i++)
        bullet[i].render();
}

vector <SDL_Rect> Enemy::getRect()
{
    return pos;
}

void Enemy::shift()
{
    int r = x;
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i].x = r;
        pos[i].y = y + pos[5].h;
        r += pos[i].w;
    }
    pos[5].x = x + (w - pos[5].w) / 2;
    pos[5].y = y;
}

int Enemy::getX()
{
    return x;
}

int Enemy::getY()
{
    return y;
}

bool Enemy::alive1()
{
    return alive;
}

// Enemy2 function

Enemy2::Enemy2(int x_, int y_)
{
    hp = 50;
    alive = true;
    img.loadfromfile("EnemyPlane22.png");
    w = img.getWidth();
    h = img.getHeight();
    x = x_;
    y = -h;
    vx = 1;
    dem = 0;

    pos.resize(3);

    pos[0].x = 0;
    pos[0].y = 0;
    pos[0].w = w * 7 / 17;
    pos[0].h = h * 2 / 9;

    pos[1].x = 0;
    pos[1].y = 0;
    pos[1].w = w * 3 / 17;
    pos[1].h = h * 5 / 9;

    pos[2].x = 0;
    pos[2].y = 0;
    pos[2].w = w * 7 / 17;
    pos[2].h = h * 2 / 9;

    shift();
}

bool Enemy2::move1()
{
    if (alive == false && bullet.size() == 0) return false;
    if (alive == true)
    {
        if (hp <= 0) alive = false;
        else
        {
            vector <SDL_Rect> tam = Plane.getRect();
            bool ok = true;
            for (int i = 0; i < tam.size(); i++)
            {
                for (int j = 0; j < pos.size(); j++)
                    if (CheckCollision(tam[i], pos[j]) == true)
                    {
                        Plane.hp -= 50;
                        alive = false;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }
        if (alive == false)
        {
                BigBang k(x, y);
                Explosions.push_back(k);
        }
        dem++;
        if (dem == 200)
        {
            EnemyBullet tam1(x + (w - Bullet_w) / 4, y + h - Bullet_h / 2);
            bullet.push_back(tam1);
            EnemyBullet tam2(x + (w - Bullet_w) * 3 / 4, y + h - Bullet_h / 2);
            bullet.push_back(tam2);
            dem = 0;
        }
    }

    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].move1() == false) bullet.erase(bullet.begin() + i);
        else i++;
    }

    if (alive == true)
    {
        if (y < 0) y += 1;
        else
        {
            SDL_Rect tam1 = {x, y, w, h};
            for (int i = 0; i < EnemyPlane.size(); i++)
                if (EnemyPlane[i].alive1() == true)
                {
                    SDL_Rect tam2 = {EnemyPlane[i].getX(), EnemyPlane[i].getY(), Plane_w, Plane_h};
                    if (CheckCollision(tam1, tam2) == true) vx = -vx;
                }
            for (int i = 0; i < EnemyPlane2.size(); i++)
                if (EnemyPlane2[i].alive1() == true)
                {
                    SDL_Rect tam2 = {EnemyPlane2[i].getX(), EnemyPlane2[i].getY(), Plane2_w, Plane2_h};
                    if (tam1 != tam2 && CheckCollision(tam1, tam2) == true) vx = -vx;
                }
            if (x + w > Width || x < 0) vx = -vx;
            x += vx;
        }
        shift();
    }
    return true;
}

void Enemy2::render()
{
    if (alive == true)
    {
        if (y < 0)
        {
            SDL_Rect tam = {0, abs(y), w, h + y};
            img.render(x, 0, &tam);
        }
        else
        {
            Object::render();
        }
    }
    for (int i = 0;i < bullet.size(); i++)
        bullet[i].render();
}

vector <SDL_Rect> Enemy2::getRect()
{
    return pos;
}

void Enemy2::shift()
{
    int r = x;
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i].x = r;
        pos[i].y = y + h * 4 / 9;
        r += pos[i].w;
    }
}

int Enemy2::getX()
{
    return x;
}

int Enemy2::getY()
{
    return y;
}

bool Enemy2::alive1()
{
    return alive;
}

//Random EnemyPlane

void sinh()
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
                int a = EnemyPlane[i].getX();
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
                int a = EnemyPlane2[i].getX();
                int b = Plane2_w;
                if (y >= a - b && y <= a + b)
                {
                    ok = false;
                    break;
                }
            }
            if (ok == true) break;
        }
        Enemy tam(y, 0);
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
                int a = EnemyPlane[i].getX();
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
                int a = EnemyPlane2[i].getX();
                int b = Plane2_w;
                if (y >= a - b && y <= a + b)
                {
                    ok = false;
                    break;
                }
            }
            if (ok == true) break;
        }
        Enemy2 tam(y, 0);
        EnemyPlane2.push_back(tam);
    }
}

//Explosions

void Exp()
{
    int i = 0;
    while (i < Explosions.size())
    {
        if (Explosions[i].render() == false) Explosions.erase(Explosions.begin() + i);
        else i++;
    }
}

//Loadmedia

void loadmedia()
{
    BG.loadfromfile("Jungle.png");
    Plane.loadfromfile("MyPlane4.png");
    int wi = 128;
    int hi = 128;
    int yi = 0;
    int dem = 0;
    for (int i = 0; i < 4; i++)
    {
        int xi = 0;
        for (int j = 0; j < 4; j++)
        {
            Explo[dem] = {xi , yi, wi, hi};
            xi += wi;
            dem++;
        }
        yi += hi;
    }
}

//Close

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    IMG_Quit();
    gRenderer = NULL;
    gWindow = NULL;
}

int main(int argc, char *args[])
{
    init();
    loadmedia();
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
            if (Plane.alive1() == true) Plane.handle(e);
        }

        BG.render(0, 0, &background);
        if (Plane.alive1() == true)
        {
            background.y -= 1;
            if (background.y < 0) background.y = Level_Height - Height;
            Plane.move1();
            int i = 0;
            while (i < EnemyPlane.size())
            {
                if (EnemyPlane[i].move1() == false) EnemyPlane.erase(EnemyPlane.begin() + i);
                else i++;
            }
            i = 0;
            while (i < EnemyPlane2.size())
            {
                if (EnemyPlane2[i].move1() == false) EnemyPlane2.erase(EnemyPlane2.begin() + i);
                else i++;
            }
            sinh();
            Plane.render();
            for (int i = 0; i < EnemyPlane.size(); i++)
                EnemyPlane[i].render();
            for (int i = 0; i < EnemyPlane2.size(); i++)
                EnemyPlane2[i].render();
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
