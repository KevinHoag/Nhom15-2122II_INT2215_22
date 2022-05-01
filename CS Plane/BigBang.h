SDL_Rect Explo[16];

class BigBang
{
    int x;
    int y;
    int w;
    int h;
    int frame;
    LTexture clip;
public:
    BigBang(int x_, int y_);
    bool render();
};

BigBang::BigBang(int x_, int y_)
{
    x = x_;
    y = y_;
    frame = 0;
    clip.loadfromfile("Explosion3.png");
    w = clip.getWidth() / 4;
    h = clip.getHeight() / 4;
}

bool BigBang::render()
{
    if (frame > 15) return false;
    clip.render(x - w / 4, y - h / 4, &Explo[frame]);
    frame++;
    return true;
}
