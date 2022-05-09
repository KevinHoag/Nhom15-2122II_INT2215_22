#ifndef EnemyPlane_h
#define EnemyPlane_h

#include <vector>
#include "EnemyBullet.h"
#include "Object.h"
#include "BigBang.h"

class Enemy: public Object
{
    int vx;
    bool alive;
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
    LTexture status;
public:
    int hp;
    Enemy(SDL_Renderer *&gRenderer, int x_ = 0, int y_ = 0);
    bool move1(SDL_Renderer *&gRenderer);
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont);
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
    friend class Enemy2;
    friend void sinh();
    friend void update();
};

#endif
