//Start up SDL and create window

void Solution() {
    val_w = SCREEN_WIDTH;
    val_h = SCREEN_HEIGHT;
    val_res = check_resolution;
    val_back = check_background;
    val_mixer = check_mixer;
    init();
    bool quit = false;
    //Event handler
    loadMedia_5();
    Mix_PlayMusic( gMusic, -1 );
    SDL_Event e;
    int keyrow = 0, next = 0;
    //While application is running
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0;
        if (val_res  == 0 && val_w == 1080 && val_h == 640) h = 100, w = 100, sum = 50, fsize = 50;
        if (val_res  == 0 && val_w == 640 && val_h == 320) h = 100, w = 50, sum = 50, fsize = 50;
        if (val_res  == 1) h = 100, w = 100, sum = 50, fsize = 50;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update(keyrow, 1);
                   break;
                   case SDLK_e:
                       exit(0);
                   break;
                   case SDLK_b:
                       keyrow = 0;
                   break;
                   case SDLK_RETURN:
                        next = 1;
                   break;
            }
         //Clear screen
        if (next == 1) {
            if (keyrow == 0) next = 0;
            else if (keyrow == 1) {
                    next = 0;
                 }
            else if (keyrow == 2) {
                    next = 0;
                    Leaderboard();
                 }
            else if (keyrow == 3) {
                    next = 0;
                    Setting();
                    close();
                    Solution();
                 }
            else if (keyrow == 4) {
                    Tutorial();
                    next = 0;
                 }
            else if (keyrow == 5) {
                    exit(0);
                 }
            continue;
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadMedia_1();
         //Render texture to screen
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
        loadMedia_2(keyrow, fsize);
        for (int i = 0; i < 5; ++ i) {
            gTextTexture[i].render(h, w, gRenderer );
            w += sum;
        }
        //Update screen
        SDL_RenderPresent( gRenderer );

    }
}
