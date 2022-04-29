#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

const int Level_Height = 4023;
const int Level_Width = 1024;
const int Height = 520;
const int Width = 1024;
const int FPS = 1000 / 60;
const int Bullet_w = 6;
const int Bullet_h = 14;
const int Plane_w = 50;
const int Plane_h = 60;
const int max1 = 100;
const int min1 = 1;

//LTexture

class LTexture
{
    int w;
    int h;
    SDL_Texture *mTexture;
public:
    LTexture();
    void loadfromfile(string path);
    void render(int x = 0, int y = 0, SDL_Rect *p = NULL);
    int getWidth();
    int getHeight();
    void close();
};

//Object

class Object
{
protected:
    int x;
    int y;
    int vx;
    int vy;
    int w;
    int h;
    static const int vt = 8;
    LTexture img;
public:
    Object(int x_ = 0, int y_ = 0);
    void render();
};

class MyBullet: public Object
{
    static const int v = 5;
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
    vector <MyBullet> bullet;
    vector <SDL_Rect> pos;
public:
    void loadfromfile(string path);
    void handle(SDL_Event &e);
    void move1();
    void render();
    vector <SDL_Rect> getRect();
    void shift();
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
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
    bool alive = true;
public:
    Enemy(int x_ = 0, int y_ = 0);
    bool move1();
    void render();
    int getX();
    int getW();
    vector <SDL_Rect> getRect();
    void shift();
};

//Global variable

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture BG;
MyPlane Plane;
vector <Enemy> EnemyPlane;

//LTexture functions

LTexture::LTexture()
{
    w = 0;
    h = 0;
    mTexture = NULL;
}

void LTexture::loadfromfile(string path)
{
    SDL_Surface *gSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(gSurface, SDL_TRUE, (gSurface->format, 255, 255, 255, 255));
    if (!gSurface)
    {
        cout << "IMG_Load failed: " << SDL_GetError() << endl;
        return;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (!mTexture) cout << "CreateTextureFromSurface failed: " << SDL_GetError() << endl;
    w = gSurface->w;
    h = gSurface->h;
    SDL_FreeSurface(gSurface);
    gSurface = NULL;
}

void LTexture::render(int x, int y, SDL_Rect *p)
{
    SDL_Rect tam = {x, y, w, h};
    if (p)
    {
        w = p->w;
        h = p->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, p, &tam);
}

int LTexture::getHeight()
{
    return h;
}

int LTexture::getWidth()
{
    return w;
}

void LTexture::close()
{
    w = 0;
    h = 0;
    mTexture = NULL;
}

//Object functions

Object::Object(int x_, int y_)
{
    x = x_;
    y = y_;
    vx = 0;
    vy = 0;
}

void Object::render()
{
    img.render(x, y);
}

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
    int i = 0;
    while (i < bullet.size())
    {
        bool ok = true;
        SDL_Rect a = bullet[i].getRect();
        for (int j = 0; j < EnemyPlane.size(); j++)
        {
            vector <SDL_Rect> b = EnemyPlane[j].getRect();
            for (int k = 0; k < b.size() - 1; k++)
                if (CheckCollision(a, b[k]) == true)
            {
                ok = false;
                bullet.erase(bullet.begin() + i);
                break;
            }
            if (ok == false) break;
        }
        bullet[i].move1();
        if (ok == true) i++;
    }
    x += vx;
    if (x < 0 || x + w > Width)  x -= vx;
    y += vy;
    if (y < 0 || y + h > Height) y -= vy;
    shift();
}

void MyPlane::render()
{
    Object::render();
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
        if (CheckCollision(tam[i], a) == true) return false;
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
    img.loadfromfile("EnemyPlane4.png");
    w = img.getWidth();
    h = img.getHeight();
    x = x_;
    y = -h;

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
    vector <SDL_Rect> tam = Plane.getRect();
    for (int i = 0; i < tam.size(); i++)
        for (int j = 0; j < pos.size(); j++)
            if (CheckCollision(tam[i], pos[j]) == true) alive = false;
    if (y % 200 == 0 && alive == true)
    {
        EnemyBullet tam(x + (w - Bullet_w) / 2, y + h - Bullet_h / 2);
        bullet.push_back(tam);
    }
    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].move1() == false) bullet.erase(bullet.begin() + i);
        else i++;
    }
    y += 1;
    shift();
    return true;
}

void Enemy::render()
{
    if (alive == true) Object::render();
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

int Enemy::getW()
{
    return w;
}

void sinh()
{
    if (EnemyPlane.size() == 3) return;
    int x = min1 + rand() % (max1 - min1);
    if (x == 5)
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane_w);
            bool ok = true;
            for (int i = 0; i < EnemyPlane.size(); i++)
            {
                int a = EnemyPlane[i].getX();
                int b = EnemyPlane[i].getW();
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
}

//Init

void init()
{
    gWindow = SDL_CreateWindow("CS Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
}

//Loadmedia

void loadmedia()
{
    BG.loadfromfile("Jungle.png");
    Plane.loadfromfile("MyPlane4.png");
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
            Plane.handle(e);
        }

        Plane.move1();
        sinh();
        background.y -= 1;
        if (background.y < 0) background.y = Level_Height - Height;
        BG.render(0, 0, &background);
        int i = 0;
        while (i < EnemyPlane.size())
        {
            if (EnemyPlane[i].move1() == false) EnemyPlane.erase(EnemyPlane.begin() + i);
            else i++;
        }
        Plane.render();
        for (int i = 0; i < EnemyPlane.size(); i++)
            EnemyPlane[i].render();
        SDL_RenderPresent(gRenderer);

        Uint32 tam2 = SDL_GetTicks() - tam1;
        if (tam2 < FPS) SDL_Delay(FPS - tam2);
    }
    close();
    return 0;
}
