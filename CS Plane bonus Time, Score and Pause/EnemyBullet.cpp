#include "EnemyBullet.h"
#include <iostream>

EnemyBullet::EnemyBullet(SDL_Renderer *&gRenderer, int x_, int y_, int diff)
{
 //   img.loadfromfile(gRenderer, "Bullet3.png");
    td = vt / 3 + diff / 30000;
    x = x_;
    y = y_;
    w = Bullet_w;
    h = Bullet_h;
    a = {x, y, w, h};
}

bool EnemyBullet::move1()
{
    if (y > Height) return false;
    y += td;
    shift();
    return true;
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

