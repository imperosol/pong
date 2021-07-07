//
// Created by thgir on 05/07/2021.
//

#ifndef PONG_STRUCT_H
#define PONG_STRUCT_H

#define and &&
#define or ||

#define PLATFORM_WIDTH 5
#define PLATFORM_HEIGHT 60

#define BALL_SIDE 15


typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int pos;
    int speed;
    int speed_multiplier;
} Platform;

typedef struct {
    Platform * platform;
    int score;
} Player;
Player player[2];

#endif //PONG_STRUCT_H
