#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(SDL_Renderer *&gRenderer, int x_, int y_)
{
    img.loadfromfile(gRenderer, "Bullet3.png");
    x = x_;
    y = y_;
    w = img.getWidth();
    h = img.getHeight();
    a = {x, y, w, h};
}

bool EnemyBullet::move1()
{
    if (y > Height) return false;
    y += vt / 3;
    shift();
    return true;
}

void EnemyBullet::render(SDL_Renderer *&gRenderer)
{
    Object::render(gRenderer);
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

