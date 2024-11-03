#ifndef SCOREBOARD_H
#define SCOREBOARD_H

typedef struct {
    int player1_score;
    int player2_score;
} Scoreboard;

void scoreboard_reset(Scoreboard *scoreboard);
void scoreboard_increment_player(Scoreboard *scoreboard);
void scoreboard_increment_ai(Scoreboard *scoreboard);

#endif 
