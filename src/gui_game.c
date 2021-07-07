//
// Created by thgir on 06/07/2021.
//

#include "../header/gui_game.h"

static void display_platforms() {
    SDL_Rect platform_rect;
    platform_rect.w = PLATFORM_WIDTH;
    platform_rect.h = PLATFORM_HEIGHT;

    // Platform for first player
    platform_rect.y = player[0].platform->pos;
    platform_rect.x = 10;
    SDL_RenderFillRect(app.renderer, &platform_rect);

    // Platform for second player
    platform_rect.y = player[1].platform->pos;
    platform_rect.x = SCREEN_WIDTH - PLATFORM_WIDTH - 10;
    SDL_RenderFillRect(app.renderer, &platform_rect);
}

static void display_background() {
    SDL_Rect rect;
    rect.x = (SCREEN_WIDTH / 2) - 2;
    rect.w = 4;
    rect.h = 25;
    for (rect.y = 10; rect.y <= SCREEN_HEIGHT; rect.y += 50) {
        SDL_RenderFillRect(app.renderer, &rect);
    }
}

static void display_digit(const int xTop, const int yTop, const int value) {
    SDL_Rect vertical_rect;
    SDL_Rect horizontal_rect;
    vertical_rect.w = horizontal_rect.h = 4;
    vertical_rect.h = horizontal_rect.w = 16;
    vertical_rect.x = horizontal_rect.x = xTop;
    vertical_rect.y = horizontal_rect.y = yTop;
    switch (value) {
        case 0:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += 28;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x += 16;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 1:
            vertical_rect.x += 8;
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 2:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.x += horizontal_rect.w - 4;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x -= horizontal_rect.w - 4;
            vertical_rect.y += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 3:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.x += horizontal_rect.w - 4;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.y += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 4:
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x += 16;
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            horizontal_rect.y += 16;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            break;
        case 5:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x += horizontal_rect.w - 4;
            vertical_rect.y += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 6:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += vertical_rect.h - 2;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.x += horizontal_rect.w - 4;
            vertical_rect.y += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x -= horizontal_rect.w;
            vertical_rect.y -= vertical_rect.h;
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 7:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.x += horizontal_rect.w;
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        case 8:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += 14;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += 14;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            vertical_rect.h += vertical_rect.h;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.x += 16;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
        default:
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += 14;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            horizontal_rect.y += 14;
            SDL_RenderFillRect(app.renderer, &horizontal_rect);
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            vertical_rect.h += vertical_rect.h;
            vertical_rect.x += 16;
            SDL_RenderFillRect(app.renderer, &vertical_rect);
            break;
    }
}

static void display_scores() {
    SDL_Rect rect;
    const int yTop = 20;
    int xTop = SCREEN_WIDTH / 2 - 40;
    for (int i = 0; i < 2; ++i, xTop += 70) {
        display_digit(xTop, yTop, player[i].score);
    }
}

static void display_ball(Ball *ball) {
    SDL_Rect rect = {ball->x, ball->y, BALL_SIDE, BALL_SIDE};
    SDL_RenderFillRect(app.renderer, &rect);
}

void present_scene(Ball *ball) {
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 240, 240, 240, 255);
    display_platforms();
    display_ball(ball);
    display_background();
    display_scores();
    SDL_RenderPresent(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 40, 40, 40, 255);
}