
int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 640;
int check_resolution = 0;
int check_background = 1;
int check_mixer = 1;
int n;
int val_w = SCREEN_WIDTH;
int val_h = SCREEN_HEIGHT;
int val_res = check_resolution;
int val_back = check_background;
int val_mixer = check_mixer;
std::string s[15];
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Globally used font
TTF_Font *gFont = NULL;


Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;



//Rendered texture
LTexture gTextTexture[10];
LTexture gTextTexture_1[10];
LTexture gTextTexture_2[15];
LTexture gTextTexture_3[5];
LTexture gTextTexture_4[5];
LTexture gTextTexture_5[5];
LTexture gTextTexture_6[5];
LTexture gTextTexture_7[5];

