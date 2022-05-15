#include <sstream>
#include "EnemyPlane2.h"

Enemy2::Enemy2(SDL_Renderer *&gRenderer, int x_, int y_)
{
    hp = 50;
    alive = true;
    img.loadfromfile(gRenderer, "EnemyPlane22.png");
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

bool Enemy2::move1(SDL_Renderer *&gRenderer)
{
    if (alive == false && bullet.size() == 0) return false;
    if (alive == true)
    {
        dem++;
        if (dem == 200)
        {
            EnemyBullet tam1(gRenderer, x + (w - Bullet_w) / 4, y + h - Bullet_h / 2);
            bullet.push_back(tam1);
            EnemyBullet tam2(gRenderer, x + (w - Bullet_w) * 3 / 4, y + h - Bullet_h / 2);
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
        if (y < status.getHeight()) y += 1;
        else
        {
            SDL_Rect tam1 = {x, y, w, h};
            if (x + w > Width || x < 0) vx = -vx;
            x += vx;
        }
        shift();
    }
    return true;
}

void Enemy2::render(SDL_Renderer *&gRenderer, TTF_Font *&gFont)
{
    if (alive == true)
    {
        if (y < 0)
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

bool Enemy2::alive1()
{
    return alive;
}
