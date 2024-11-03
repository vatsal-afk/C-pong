#include "../include/game.h"

void game_init(Game *game) {
    game_window_init(&game->window);
    g_signal_connect(game->window->drawing_area, "draw", G_CALLBACK(game_window_draw), game);

    // Start the GTK main loop to display the window and handle events
    gtk_main();
}

void game_run(Game *game) {

}

void game_update(Game *game) {

}

void game_render(Game *game) {

}

void game_cleanup(Game *game) {

}