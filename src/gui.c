//
// Created by thgir on 05/07/2021.
//

#include "../header/gui.h"

void initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("window initialization failure due to : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
//    if (IMG_Init(IMG_INIT_PNG) == -1) {
//        printf("window initialization failure due to");
//        exit(EXIT_FAILURE);
//    }
//    if (SDL_Init(TTF_Init()) == -1) {
//        printf("window initialization failure due to");
//        exit(EXIT_FAILURE);
//    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}


void create_window(const char *title) {
    app.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
}

void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void framerate_manager(Uint32 oldTick) {
    static const double frameTime = 1000.0f / FPS;
    Uint32 elapsed = SDL_GetTicks() - oldTick;
//    printf("%d\n", elapsed);
    if (elapsed < frameTime) {
        SDL_Delay((Uint32)frameTime - elapsed);
    }
}