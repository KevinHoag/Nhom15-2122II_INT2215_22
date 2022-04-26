void S_background() {
    bool quit = false; int next = 0, keyrow = 0;
    SDL_Event e;
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0;
        if (val_res  == 0 && val_w == 1080 && val_h == 640) h = 100, w = 100, sum = 50, fsize = 50;
        if (val_res  == 0 && val_w == 640 && val_h == 320) h = 100, w = 50, sum = 50, fsize = 50;
        if (val_res  == 1) h = 100, w = 100, sum = 50, fsize = 50;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update_3(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update_3(keyrow, 1);
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
               check_background = 1;
            }
            if (keyrow == 2) {
                check_background = 2;
            }
            if (keyrow == 3) {
                check_background = 3;
            }
            if (keyrow == 4) quit = 1;
            next = 0;
        }
        if (quit == 1) {
            Accept();
            continue;
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadMedia_1();
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
        loadMedia_9(keyrow, fsize);
        for (int i = 0; i < 4; ++ i) {
            gTextTexture_6[i].render(h, w, gRenderer );
            w += sum;
        }
        SDL_RenderPresent( gRenderer );
    }
}


