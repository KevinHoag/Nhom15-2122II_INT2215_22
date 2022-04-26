void Accept() {
    bool quit = false; int next = 0, keyrow = 0;
    SDL_Event e;
    while( !quit ) {
        int h = 200, w = 200;
        if (val_res  == 0 && val_w == 640 && val_h == 320) h = 100, w = 60;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update_4(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update_4(keyrow, 1);
                   break;
                   case SDLK_b:
                       quit = 1;
                   break;
                   case SDLK_RETURN:
                       next = 1;
                   break;
            }
        if (next) {
            if (keyrow == 1) {
                quit = 1;
            }
            if (keyrow == 2) {
               SCREEN_WIDTH = val_w; SCREEN_HEIGHT = val_h; check_resolution = val_res; check_background = val_back; check_mixer = val_mixer;
               quit = 1;
            }
            continue;
        }
        if (quit == 1) {
            continue;
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadMedia_1();
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
        loadMedia_8(keyrow);
        for (int i = 0; i < 2; ++ i) {
            gTextTexture_5[i].render(h, w, gRenderer );
            w += 150;
        }
        SDL_RenderPresent( gRenderer );
    }
}


