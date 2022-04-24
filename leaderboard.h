void Leaderboard() {
    bool quit = false; int next = 0, keyrow = 0;
    SDL_Event e;
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0;
        if (val_res  == 0 && val_w == 1080 && val_h == 640) h = 50, w = 20, sum = 50, fsize = 50;
        if (val_res  == 0 && val_w == 640 && val_h == 320) h = 20, w = 10, sum = 25, fsize = 30;
        if (val_res  == 1) h = 50, w = 10, sum = 40, fsize = 30;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_UP:
                       keyrow = Update_2(keyrow, -1);
                   break;
                   case SDLK_DOWN:
                       keyrow = Update_2(keyrow, 1);
                   break;
                   case SDLK_b:
                       quit = 1;
                   break;
                   case SDLK_RETURN:
                       next = 1;
                   break;
            }
        if (next) {
            if (keyrow == 12) quit = 1;
            next = 0;
            continue;
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadMedia_1();
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
        loadMedia_3(keyrow, fsize);
        for (int i = 0; i < 12; ++ i) {
            gTextTexture_2[i].render(h, w, gRenderer );
            w += sum;
        }
        SDL_RenderPresent( gRenderer );
    }
}
