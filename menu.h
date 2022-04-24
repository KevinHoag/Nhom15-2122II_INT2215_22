bool init();

bool loadMedia_1();
bool loadMedia_2();
bool loadMedia_3();
bool loadMedia_4();
bool loadMedia_5();
bool loadMedia_6();
bool loadMedia_7();
bool loadMedia_8();
bool loadMedia_9();
bool loadMedia_10();
void close();

SDL_Texture* loadTexture( std::string path );

int Update();
int Update_2();
int Update_3();
int Update_4();

void Solution();
void Leaderboard();
void Tutorial();
void Setting();

void S_resolution();
void S_background();
void S_music();
void Accept();

bool init()
{
	//Initialization flag
	bool success = true;

	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
	if (check_resolution) gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN );
	else gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	int imgFlags = IMG_INIT_PNG;
	IMG_Init( imgFlags );
	TTF_Init();
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	return success;
}

bool loadMedia_1()
{
	bool success = true;
	if (check_background == 1) gTexture = loadTexture( "zz.png" );
    if (check_background == 2) gTexture = loadTexture( "z2.png" );
    if (check_background == 3) gTexture = loadTexture( "z3.png" );
	return success;
}

bool loadMedia_2(int x, int fsize)
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", fsize );

    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture[0].loadFromRenderedText( "PLAY", textColor2, gFont, gRenderer );
    else gTextTexture[0].loadFromRenderedText( "PLAY", textColor, gFont, gRenderer );
    if (x == 2) gTextTexture[1].loadFromRenderedText( "LEADERBOARD", textColor2, gFont, gRenderer );
    else gTextTexture[1].loadFromRenderedText( "LEADERBOARD", textColor, gFont, gRenderer );
    if (x == 3) gTextTexture[2].loadFromRenderedText( "SETTING", textColor2, gFont, gRenderer );
    else gTextTexture[2].loadFromRenderedText( "SETTING", textColor, gFont, gRenderer );
    if (x == 4) gTextTexture[3].loadFromRenderedText( "TUTORIAL", textColor2, gFont, gRenderer );
    else gTextTexture[3].loadFromRenderedText( "TUTORIAL", textColor, gFont, gRenderer );
    if (x == 5) gTextTexture[4].loadFromRenderedText( "EXIT", textColor2, gFont, gRenderer );
    else gTextTexture[4].loadFromRenderedText( "EXIT", textColor, gFont, gRenderer );
	return success;
}

bool loadMedia_3(int x, int fsize)
{
	//Loading success flag
	bool success = true;
	int fsize1 = 0;
    if (fsize == 50) fsize1 = 30;
    else if (fsize == 30) fsize1 = 15;
	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {55, 155, 0};
    if (x == 1) gTextTexture_2[0].loadFromRenderedText( "LEADERBOARD", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_2[0].loadFromRenderedText( "LEADERBOARD", textColor3, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );

    for (int i = 1; i <= n; ++ i) {
        if (x == i + 1) gTextTexture_2[i].loadFromRenderedText( s[i], textColor2, TTF_OpenFont( "lazy.ttf", fsize1 ), gRenderer );
        else gTextTexture_2[i].loadFromRenderedText( s[i], textColor, TTF_OpenFont( "lazy.ttf", fsize1 ), gRenderer );
    }

    if (x == 12) gTextTexture_2[11].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_2[11].loadFromRenderedText( "BACK", textColor3, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
	return success;
}
bool loadMedia_4(int fsize) {
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    int fsize1 = 0;
    if (fsize == 50) fsize1 = 30;
    else if (fsize == 30) fsize1 = 15;
    gTextTexture_1[0].loadFromRenderedText("wuyrwueruewrwehurwehruweruehruewhehwuwrsfdsdsfdsfdsfdsfdfdsfdsfdsfdsruwherwueh", textColor, gFont = TTF_OpenFont( "lazy.ttf", fsize ), gRenderer);
    gTextTexture_1[8].loadFromRenderedText("Nguyen Thanh Son && Hoang Minh Quang", textColor, gFont = TTF_OpenFont( "lazy.ttf", 30 ), gRenderer);
    gTextTexture_1[9].loadFromRenderedText("BACK", textColor2, gFont = TTF_OpenFont( "lazy.ttf", 70 ), gRenderer);
    return 1;
}
bool loadMedia_5() {
    if (check_mixer == 1) gMusic = Mix_LoadMUS( "ft.mp3" );
    if (check_mixer == 2) gMusic = Mix_LoadMUS( "h3.mp3" );
    if (check_mixer == 3) gMusic = Mix_LoadMUS( "h2.mp3" );
    return 1;
}
bool loadMedia_6(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_3[0].loadFromRenderedText( "RESOLUTION", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[0].loadFromRenderedText( "RESOLUTION", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_3[1].loadFromRenderedText( "BACKGROUND", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[1].loadFromRenderedText( "BACKGROUND", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_3[2].loadFromRenderedText( "MUSIC", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[2].loadFromRenderedText( "MUSIC", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_3[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_3[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_7(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_4[0].loadFromRenderedText( "AUTO-RESOLUTION", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[0].loadFromRenderedText( "AUTO-RESOLUTION", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_4[1].loadFromRenderedText( "640 * 320", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[1].loadFromRenderedText( "640 * 320", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_4[2].loadFromRenderedText( "FULLSCREEN", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[2].loadFromRenderedText( "FULLSCREEN", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_4[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_4[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_8(int x) {
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_5[0].loadFromRenderedText( "YES", textColor2, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    else gTextTexture_5[0].loadFromRenderedText( "YES", textColor, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    if (x == 2) gTextTexture_5[1].loadFromRenderedText( "NO", textColor2, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    else gTextTexture_5[1].loadFromRenderedText( "NO", textColor, TTF_OpenFont( "lazy.ttf", 100 ), gRenderer );
    return 1;
}
bool loadMedia_9(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) gTextTexture_6[2].loadFromRenderedText( "STARWAR", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[2].loadFromRenderedText( "STARWAR", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_6[1].loadFromRenderedText( "FARMLAND", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[1].loadFromRenderedText( "FARMLAND", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 1) gTextTexture_6[0].loadFromRenderedText( "AUTO-SCREEN", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[0].loadFromRenderedText( "AUTO-SCREEN", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_6[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_6[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    return 1;
}
bool loadMedia_10(int x, int fsize) {
    gFont = TTF_OpenFont( "lazy.ttf", fsize );
    SDL_Color textColor = { 0, 0, 0 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) gTextTexture_7[0].loadFromRenderedText( "AUTO-MUSIC", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[0].loadFromRenderedText( "AUTO-MUSIC", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 2) gTextTexture_7[1].loadFromRenderedText( "HHH", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[1].loadFromRenderedText( "HHH", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 3) gTextTexture_7[2].loadFromRenderedText( "ZZZ", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[2].loadFromRenderedText( "ZZZ", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    if (x == 4) gTextTexture_7[3].loadFromRenderedText( "BACK", textColor2, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
    else gTextTexture_7[3].loadFromRenderedText( "BACK", textColor, TTF_OpenFont( "lazy.ttf", fsize ), gRenderer );
}
void close()
{
    Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

    Mix_FreeMusic( gMusic );
	gMusic = NULL;
    //Free loaded images
    for (int i = 0; i < 5; ++ i)
        gTextTexture[i].free();

    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();
}


SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

	return newTexture;
}

int Update(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 5;
    if (keyrow == 1 && x == -1) return 5;
    if (keyrow == 5 && x == 1) return 1;
    return keyrow + x;
}
int Update_2(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 12;
    if (keyrow == 1 && x == -1) return 12;
    if (keyrow == 12 && x == 1) return 1;
    return keyrow + x;
}
int Update_3(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 4;
    if (keyrow == 1 && x == -1) return 4;
    if (keyrow == 4 && x == 1) return 1;
    return keyrow + x;
}
int Update_4(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 2;
    if (keyrow == 1 && x == -1) return 2;
    if (keyrow == 2 && x == 1) return 1;
    return keyrow + x;
}
