#include "MyBullet.h"

MyBullet::MyBullet(SDL_Renderer *&gRenderer, int x_, int y_)
{
    img.loadfromfile(gRenderer, "Bullet3.png");
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

bool MyBullet::render(SDL_Renderer *&gRenderer)
{
    if (y < 0)
    {
        return false;
    }
    Object::render(gRenderer);
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
