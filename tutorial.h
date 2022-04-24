void Tutorial() {
    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        int h = 0, w = 0, sum = 0, fsize = 0;
        if (val_res  == 0 && val_w == 1080 && val_h == 640) h = 20, w = 20, sum = 50, fsize = 50;
        if (val_res  == 0 && val_w == 640 && val_h == 320) h = 20, w = 10, sum = 25, fsize = 30;
        if (val_res  == 1) h = 50, w = 20, sum = 20, fsize = 30;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
            switch( e.key.keysym.sym ) {
                   case SDLK_b:
                       quit = 1;
                   break;
            }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadMedia_1();
        SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
        loadMedia_4(fsize);
        for (int i = 0; i < 10; ++ i) {
            gTextTexture_1[i].render(h, w, gRenderer );
            w += sum;
        }
        SDL_RenderPresent( gRenderer );
    }
}
