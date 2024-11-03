#include <gtk/gtk.h>
#include "../include/game.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);  

    Game game;              
    game_init(&game);         
    // game_run(&game);
    // game_cleanup(&game); 

    return 0;
}
