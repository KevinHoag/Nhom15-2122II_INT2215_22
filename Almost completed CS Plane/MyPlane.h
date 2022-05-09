#ifndef MyPlane_h
#define MyPlane_h

#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "Object.h"
#include "MyBullet.h"
#include "BigBang.h"

class MyPlane: public Object
{
    int vx = 0;
    int vy = 0;
    vector <MyBullet> bullet;
    vector <SDL_Rect> pos;
    bool alive;
    LTexture status;
public:
    int hp;
    void loadfromfile(SDL_Renderer *&gRenderer, string path);
    void handle(SDL_Renderer *&gRenderer, SDL_Event &e);
    void move1();
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont);
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
    friend class HP;
    friend void update();
};

#endif
