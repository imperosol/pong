//
// Created by thgir on 05/07/2021.
//

#ifndef PONG_GUI_H
#define PONG_GUI_H

#include <stdio.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>

#include "struct.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

#define FPS 60

void initialize_SDL();
void create_window(const char *title);
void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h);
void framerate_manager(Uint32 oldTick);


struct App {
    SDL_Renderer * renderer;
    SDL_Window * window;
};
struct App app;
#endif //PONG_GUI_H
