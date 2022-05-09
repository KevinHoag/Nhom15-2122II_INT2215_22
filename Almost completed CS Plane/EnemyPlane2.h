#ifndef EnemyPlane2_h
#define EnemyPlane2_h

#include <vector>
#include "EnemyBullet.h"
#include "Object.h"

class Enemy2: public Object
{
    int vx;
    int dem;
    bool alive = false;
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
    LTexture status;
public:
    int hp;
    Enemy2(SDL_Renderer *&gRenderer, int x_ = 0, int y_ = 0);
    bool move1(SDL_Renderer *&gRenderer);
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont);
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
    friend class Enemy;
    friend void sinh();
    friend void update();
};

#endif
