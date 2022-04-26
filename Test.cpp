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
const int Bullet_w = 7;
const int Bullet_h = 19;
const int Plane_w = 48;
const int Plane_h = 65;
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
    static const int vt = 10;
    LTexture img;
public:
    Object(int x_ = 0, int y_ = 0);
    void render(int x_ = -1, int y_ = -1, SDL_Rect *p = NULL);
};

class MyBullet: public Object
{
    static const int v = 5;
public:
    MyBullet(int x_ = 0, int y_ = 0);
    void move1();
    bool render();
};

class MyPlane: public Object
{
    vector <MyBullet> bullet;
public:
    void loadfromfile(string path);
    void handle(SDL_Event &e);
    void move1();
    void render();
};

class EnemyBullet: public Object
{
    static const int v = 3;
public:
    EnemyBullet(int x_ = 0, int y_ = 0);
    void move1();
    bool render();
};

class Enemy: public Object
{
    vector <EnemyBullet> bullet;
public:
    Enemy(int x_ = 0, int y_ = 0);
    void move1();
    bool render();
    int getX();
    int getW();
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
    SDL_SetColorKey(gSurface, SDL_TRUE, (gSurface->format, 0, 0, 0));
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

void Object::render(int x_, int y_, SDL_Rect *p)
{
    if (x_ != -1 && y_ != -1) img.render(x_, y_, p);
    else if (x_ != -1) img.render(x_, y, p);
    else if (y_ != -1) img.render(x, y_, p);
    else img.render(x, y, p);
}

//MyBullet functions

MyBullet::MyBullet(int x_, int y_)
{
    img.loadfromfile("Bullet.png");
    x = x_;
    y = y_;
}

void MyBullet::move1()
{
    y -= 5;
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

//MyPlane functions

void MyPlane::loadfromfile(string path)
{
    img.loadfromfile(path.c_str());
    w = img.getWidth();
    h = img.getHeight();
    x = (Width - w) / 2;
    y = Height - h;
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

    for (int i = 0; i < bullet.size(); i++) bullet[i].move1();
    x += vx;
    if (x < 0 || x + w > Width)  x -= vx;
    y += vy;
    if (y < 0 || y + h > Height) y -= vy;
}

void MyPlane::render()
{
    Object::render();
    for (int i = 0; i < bullet.size(); i++)
        if (bullet[i].render() == false) bullet.erase(bullet.begin() + i);
}

//EnemyBullet functions

EnemyBullet::EnemyBullet(int x_, int y_)
{
    img.loadfromfile("Bullet.png");
    x = x_;
    y = y_;
}

void EnemyBullet::move1()
{
    y += v;
}

bool EnemyBullet::render()
{
    if (y > Height) return false;
    Object::render();
    return true;
}

//Enemy functions

Enemy::Enemy(int x_, int y_)
{
    img.loadfromfile("Entities3.png");
    x = x_;
    y = -Plane_h;
    w = img.getWidth();
    h = img.getHeight();
}

void Enemy::move1()
{
    if (bullet.size() == 0 && y > 0)
    {
        EnemyBullet tam(x + (w - Bullet_w) / 2, y + h - Bullet_h / 2);
        bullet.push_back(tam);
    }
    for (int i = 0;i < bullet.size(); i++)
        bullet[i].move1();
    y += 1;
}

bool Enemy::render()
{
    if (y > Height) return false;
    if (y <= 0)
    {
        SDL_Rect tam = {0, abs(y), w, Plane_h + y};
        Object::render(-1, 0, &tam);
    }
    else Object::render();
    for (int i = 0; i < bullet.size(); i++)
        if (bullet[i].render() == false) bullet.erase(bullet.begin() + i);
    return true;
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
            y = 100 + rand() % 500;
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
    Plane.loadfromfile("Entities2.png");
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
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        background.y -= 5;
        if (background.y < 0) background.y = Level_Height - Height;
        BG.render(0, 0, &background);
        Plane.render();
        for (int i = 0; i < EnemyPlane.size(); i++)
            EnemyPlane[i].move1();
        for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].render() == false) EnemyPlane.erase(EnemyPlane.begin() + i);
        SDL_RenderPresent(gRenderer);

        Uint32 tam2 = SDL_GetTicks() - tam1;
        if (tam2 < FPS) SDL_Delay(FPS - tam2);
    }
    close();
    return 0;
}
