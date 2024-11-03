#include "../include/game_window.h"
#include "../include/game.h"

void game_window_init(GameWindow *window) {
    // Initialize the GTK window and set up drawing context
    window->gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window->gtk_window), "Pong Game");
    gtk_window_set_default_size(GTK_WINDOW(window->gtk_window), 800, 600);

    // Connect the draw signal to render content
    g_signal_connect(window->gtk_window, "draw", G_CALLBACK(game_window_draw), window);

    // Show all widgets within the window
    gtk_widget_show_all(window->gtk_window);
}


gboolean game_window_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GameWindow *window = (GameWindow *)data;
if (window == NULL) {
        // Handle error: window is NULL
        return; // or some error handling
    }
    // Set background color
    cairo_set_source_rgb(cr, 1, 1, 1);  // white background
    cairo_paint(cr);

    // Draw a sample rectangle as a placeholder for game objects
    cairo_set_source_rgb(cr, 0, 0, 0);  // black color for game objects
    cairo_set_line_width(cr, 2);
    cairo_rectangle(cr, 100, 100, 50, 50);  // Replace with game object positions
    cairo_stroke(cr);
    return TRUE;

    // More drawing code for ball, paddles, etc., would go here
}

