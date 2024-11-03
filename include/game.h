#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "paddle.h"
#include "scoreboard.h"
#include "game_window.h"

typedef struct {
    Ball ball;    
    Paddle paddle1, paddle2;          
    Scoreboard scoreboard;    
    GameWindow *window;    
    int isRunning;      
} Game;

void game_init(Game *game);
void game_run(Game *game);
void game_update(Game *game);
void game_render(Game *game);
void game_cleanup(Game *game);

#endif