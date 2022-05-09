#include "BigBang.h"

BigBang::BigBang(SDL_Renderer *&gRenderer, int x_, int y_)
{
    x = x_;
    y = y_;
    frame = 0;
    clip.loadfromfile(gRenderer, "Explosion3.png");
    w = clip.getWidth() / 4;
    h = clip.getHeight() / 4;
    int wi = 128;
    int hi = 128;
    int yi = 0;
    int dem = 0;
    for (int i = 0; i < 4; i++)
    {
        int xi = 0;
        for (int j = 0; j < 4; j++)
        {
            Explo[dem] = {xi , yi, wi, hi};
            xi += wi;
            dem++;
        }
        yi += hi;
    }
}

bool BigBang::render(SDL_Renderer *&gRenderer)
{
    if (frame > 15) return false;
    clip.render(gRenderer, x - w / 4, y - h / 4, &Explo[frame]);
    frame++;
    return true;
}


