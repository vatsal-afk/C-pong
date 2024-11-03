#ifndef PADDLE_H
#define PADDLE_H

typedef struct {
    float x, y;
    float width, height;
    float speed;
} Paddle;

void paddle_init(Paddle *paddle);
void paddle_update(Paddle *paddle, int direction);

#endif 
