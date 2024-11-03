#ifndef BALL_H
#define BALL_H

#include "paddle.h"

typedef struct {
    float x, y;         
    float vx, vy;   
    float radius;  
} Ball;

void ball_init(Ball *ball);
void ball_update(Ball *ball);
void ball_check_collision(Ball *ball, Paddle *paddle);

#endif 
