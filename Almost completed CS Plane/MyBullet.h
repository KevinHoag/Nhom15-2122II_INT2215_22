#ifndef MyBullet_h
#define MyBullet_h

#include "Object.h"

class MyBullet: public Object
{
    SDL_Rect a;
public:
    MyBullet(SDL_Renderer *&gRenderer, int x_ = 0, int y_ = 0);
    void move1();
    bool render(SDL_Renderer *&gRenderer);
    SDL_Rect &getRect();
    void shift();
    friend void update();
};

#endif
