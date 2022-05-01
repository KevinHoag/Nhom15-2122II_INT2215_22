#include "LTexture.h"

class Object
{
protected:
    int x;
    int y;
    int w;
    int h;
    static const int vt = 8;
    LTexture img;
public:
    Object(int x_ = 0, int y_ = 0);
    void render();
};

Object::Object(int x_, int y_)
{
    x = x_;
    y = y_;
}

void Object::render()
{
    img.render(x, y);
}
