#include "header/nyanpasu_lib.h"
#include "header/main_game.h"
#include "header/gui.h"
#include "header/gui_game.h"
#include "header/control.h"
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    Uint32 old;
    Ball ball;

    initialize_SDL();
    create_window("pong");
    initialize_game(&ball);

    SDL_Event event;
    SDL_bool run = SDL_TRUE;
    while (run) {
        old = SDL_GetTicks();
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        run = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    event_key_down(event.key.keysym);
                    break;
                case SDL_KEYUP:
                    event_key_up(event.key.keysym);
                    break;
                default:
                    break;
            }
        }
        move_platforms();
        move_ball(&ball);
        present_scene(&ball);
        framerate_manager(old);
    }
    for (int i = 0; i < 2; ++i) {
        free(player[0].platform);
    }
    return 0;
}
