using namespace std;

const int Height = 520;
const int Width = 1024;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

void init()
{
    gWindow = SDL_CreateWindow("CS Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
}
