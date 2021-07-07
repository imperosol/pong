//
// Created by thgir on 06/07/2021.
//

#include "../header/control.h"

static void initialize_ball(Ball *ball) {
    ball->x = (SCREEN_WIDTH - BALL_SIDE) / 2;
    ball->y = (SCREEN_HEIGHT - BALL_SIDE) / 2;
    ball->dx = rand() % 2 ? 10 : -10;
    ball->dy = 0;
}

void initialize_game(Ball *ball) {
    // initialize players
    for (int i = 0; i < 2; ++i) {
        player[i].score = 0;
        player[i].platform = safe_malloc(sizeof(Platform));
        player[i].platform->pos = (SCREEN_HEIGHT - PLATFORM_HEIGHT) / 2;
        player[i].platform->speed = 0;
        player[i].platform->speed_multiplier = 1;
    }
    initialize_ball(ball);
}

void event_key_down(SDL_Keysym keysym) {
    switch (keysym.sym) {
        case SDLK_DOWN:
            player[1].platform->speed = PLATFORM_SPEED;
            break;
        case SDLK_UP:
            player[1].platform->speed = -PLATFORM_SPEED;
            break;
        case SDLK_s:
            player[0].platform->speed = PLATFORM_SPEED;
            break;
        case SDLK_z:
            player[0].platform->speed = -PLATFORM_SPEED;
            break;
        case SDLK_LSHIFT:
            player[0].platform->speed_multiplier = 2;
        case SDLK_RSHIFT:
            player[1].platform->speed_multiplier = 2;
        default:
            break;
    }
}

void event_key_up(SDL_Keysym keysym) {
    switch (keysym.sym) {
        case SDLK_DOWN:
            player[1].platform->speed = 0;
            break;
        case SDLK_UP:
            player[1].platform->speed = 0;
            break;
        case SDLK_s:
            player[0].platform->speed = 0;
            break;
        case SDLK_z:
            player[0].platform->speed = 0;
            break;
        case SDLK_LSHIFT:
            player[0].platform->speed_multiplier = 1;
        case SDLK_RSHIFT:
            player[1].platform->speed_multiplier = 1;
        default:
            break;
    }
}

void move_platforms() {
    for (int i = 0; i < 2; ++i) {
        player[i].platform->pos += player[i].platform->speed * player[i].platform->speed_multiplier;
        if (player[i].platform->pos < 0) {
            player[i].platform->pos = 0;
        } else if (player[i].platform->pos + PLATFORM_HEIGHT > SCREEN_HEIGHT) {
            player[i].platform->pos = SCREEN_HEIGHT - PLATFORM_HEIGHT;
        }
    }
}

static int ball_is_aligned_with_platform(Ball *ball, Platform *platform) {
    return platform->pos - BALL_SIDE - 1 < ball->y and ball->y < platform->pos + PLATFORM_HEIGHT + 1;
}

static int is_ball_catchable(Ball *ball) {
    // On regarde si, lors de la frame précédente, la balle se trouvait entre les deux plateformes
    int previous_pos = ball->x - ball->dx;
    return previous_pos > PLATFORM_WIDTH + 10 and previous_pos < SCREEN_WIDTH - PLATFORM_WIDTH - 10;
}

static int is_ball_out_of_screen(Ball *ball) {
    return ball->x > SCREEN_WIDTH or ball->x < -BALL_SIDE;
}

static void collision_with_platforms(Ball *ball) {
    if (ball->x + BALL_SIDE > SCREEN_WIDTH - PLATFORM_WIDTH - 10 and is_ball_catchable(ball)) {
        // collision with right platform
        if (ball_is_aligned_with_platform(ball, player[1].platform)) {
            ball->x = SCREEN_WIDTH - PLATFORM_WIDTH - 10 - BALL_SIDE;
            ball->dx = -ball->dx;
            ball->dy += (player[1].platform->speed * player[1].platform->speed_multiplier) / 2;
        }
    } else if (ball->x < PLATFORM_WIDTH + 10 and is_ball_catchable(ball)) {
        // collision with left platform
        if (ball_is_aligned_with_platform(ball, player[0].platform)) {
            ball->x = PLATFORM_WIDTH + 10;
            ball->dx = -ball->dx;
            ball->dy += (player[0].platform->speed * player[0].platform->speed_multiplier) / 2;
        }
    }
}

void move_ball(Ball *ball) {
    ball->x += ball->dx;
    ball->y += ball->dy;
    if (ball->y < 0) {
        ball->y = 0;
        ball->dy = -ball->dy;
    } else if (ball->y > SCREEN_HEIGHT - BALL_SIDE) {
        ball->y = SCREEN_HEIGHT - BALL_SIDE;
        ball->dy = -ball->dy;
    }
    collision_with_platforms(ball);
    if (is_ball_out_of_screen(ball)) {
        int winner = ball->x > 0 ? 1 : 0;
        player[winner].score++;
        initialize_ball(ball);
        player[0].platform->pos = player[1].platform->pos = (SCREEN_HEIGHT - PLATFORM_HEIGHT) / 2;
    }
}