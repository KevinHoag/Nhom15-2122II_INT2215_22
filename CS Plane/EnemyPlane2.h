#ifndef EnemyPlane2_h
#define EnemyPlane2_h

#include <vector>
#include <SDL.h>
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
    Enemy2(SDL_Renderer *&gRenderer, int x_ , int y_, int diff);
    bool move1(SDL_Renderer *&gRenderer, int diff);
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture EPlane2 ,LTexture &Bullet);
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
    void close();
    friend class Enemy;
    friend void sinh(SDL_Renderer *&gRenderer, int sl1, int sl2);
    friend void update(SDL_Renderer *&gRenderer);
    friend void reset();
};

#endif
