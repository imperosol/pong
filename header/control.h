//
// Created by thgir on 06/07/2021.
//

#ifndef PONG_CONTROL_H
#define PONG_CONTROL_H

#include "struct.h"
#include "gui.h"
#include "nyanpasu_lib.h"

#define PLATFORM_SPEED 4

void initialize_game(Ball *ball);
void event_key_down(SDL_Keysym keysym);
void event_key_up(SDL_Keysym keysym);
void move_platforms();
void move_ball(Ball * ball);

#endif //PONG_CONTROL_H
