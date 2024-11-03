#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <gtk/gtk.h>

// Define GameWindow struct with GTK window and drawing area components
typedef struct {
    GtkWidget *gtk_window;      // Main application window
    GtkWidget *drawing_area;    // Drawing area for rendering game objects
} GameWindow;

// Initializes the game window
void game_window_init(GameWindow *window);

// Draw callback function for the game window (matches GTK's callback signature)
gboolean game_window_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

#endif
