#ifndef EnemyBullet_h
#define EnemyBullet_h

#include "Object.h"

class EnemyBullet: public Object
{
    SDL_Rect a;
public:
    EnemyBullet(SDL_Renderer *&gRenderer, int x_ = 0, int y_ = 0);
    bool move1();
    void render(SDL_Renderer *&gRenderer);
    SDL_Rect &getRect();
    void shift();
    friend void update();
};

#endif

