#include <sstream>
#include "EnemyPlane.h"

Enemy::Enemy(SDL_Renderer *&gRenderer, int x_, int y_)
{
    hp = 30;
    img.loadfromfile(gRenderer, "EnemyPlane4.png");
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

bool Enemy::move1(SDL_Renderer *&gRenderer)
{
    if (y > Height) return false;
    if (alive == false && bullet.size() == 0) return false;
    if (alive == true)
    {
        if (y % 200 == 0)
        {
            EnemyBullet tam(gRenderer, x + (w - Bullet_w) / 2, y + h - Bullet_h / 2);
            bullet.push_back(tam);
        }
    }
    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].move1() == false) bullet.erase(bullet.begin() + i);
        else i++;
    }
    if (x + w > Width || x < 0) vx = -vx;
    y += 1;
    x += vx;
    shift();

    return true;
}

void Enemy::render(SDL_Renderer *&gRenderer, TTF_Font *&gFont)
{
    if (alive == true)
    {
        if (y <= 0)
        {
            SDL_Rect tam = {0, abs(y), w, h + y};
            img.render(gRenderer, x, 0, &tam);
        }
        else
        {
            Object::render(gRenderer);
        }
        stringstream ss;
        ss.str("");
        ss << " HP:" << hp;
        status.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);
        status.render(gRenderer, x + (w - status.getWidth()) / 2, y - status.getHeight());
    }
    for (int i = 0; i < bullet.size(); i++)
        bullet[i].render(gRenderer);
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

bool Enemy::alive1()
{
    return alive;
}
