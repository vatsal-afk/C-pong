#include <gtk/gtk.h>

typedef struct {
    float x, y;         
    float width, height;
    float speed;
} Paddle;

Paddle paddle1, paddle2;

typedef struct {
    float x, y;         
    float vx, vy;   
    float radius;  
} Ball;

Ball ball;

// void ball_init(Ball *ball) {
//     ball.x = 400;
//     ball.y = 300;
//     ball.vx = 30;
//     ball.vy = 40;
//     ball.radius = 10;
// }

void ball_update(Ball *ball) {

}

void ball_check_collision(Ball *ball, Paddle *paddle) {

}

void game_window_draw(GtkWidget *widget, cairo_t *cr) {
    // Set paddle color (blue)
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0); 
    // Draw the paddle
    cairo_rectangle(cr, paddle1.x, paddle1.y, paddle1.width, paddle1.height);
    cairo_fill(cr);
    cairo_rectangle(cr, paddle2.x, paddle2.y, paddle2.width, paddle2.height);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0); 
    cairo_arc(cr, ball.x, ball.y, ball.radius, 0, 2 * G_PI);

    cairo_fill(cr);
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    // Move the paddle based on arrow key input
    if (event->keyval == GDK_KEY_Up) {
        paddle1.y -= paddle1.speed; // Move up
    } else if (event->keyval == GDK_KEY_Down) {
        paddle1.y += paddle1.speed; // Move down
    }

    // Ensure paddle doesn't go out of bounds
    if (paddle1.y < 0) {
        paddle1.y = 0; // Stop at top edge
    } else if (paddle1.y > 600 - paddle1.height) {
        paddle1.y = 600 - paddle1.height; // Stop at bottom edge
    }
    if (event->keyval == 119) { // W key
    paddle2.y -= paddle2.speed;
} else if (event->keyval == 115) { // S key
    paddle2.y += paddle2.speed;
}
 // current problem when one player is moving other player starts 
 //moving then the other one takes control both should be able to move simultaneously

    // Ensure paddle doesn't go out of bounds
    if (paddle2.y < 0) {
        paddle2.y = 0; // Stop at top edge
    } else if (paddle2.y > 600 - paddle2.height) {
        paddle2.y = 600 - paddle2.height; // Stop at bottom edge
    }

    // Redraw the window
    gtk_widget_queue_draw(widget);
    return TRUE;
}

void game_window_init(GtkWidget *window) {
    // Initialize paddle properties
    paddle1.x = 10;       // Paddle x-position
    paddle1.y = 250;      // Paddle y-position
    paddle1.width = 10;   // Paddle width
    paddle1.height = 100; // Paddle height
    paddle1.speed = 10;   // Paddle movement speed

    paddle2.x = 780;       // Paddle x-position
    paddle2.y = 250;      // Paddle y-position
    paddle2.width = 10;   // Paddle width
    paddle2.height = 100; // Paddle height
    paddle2.speed = 10;   // Paddle movement speed

    ball.x = 400;
    ball.y = 300;
    ball.vx = 30;
    ball.vy = 40;
    ball.radius = 10;

    // Create a drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area); // Add drawing area to the window
    g_signal_connect(drawing_area, "draw", G_CALLBACK(game_window_draw), NULL); // Connect draw signal
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL); // Connect key press signal

    gtk_widget_set_size_request(drawing_area, 800, 600); // Set size for drawing area
    gtk_widget_show_all(window); // Show all widgets in the window
    gtk_widget_grab_focus(window); // Ensure the window has focus
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Create the main application window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pong Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    // Handle the delete event to quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Initialize the game window
    game_window_init(window);

    // Start the GTK main loop
    gtk_main();
    return 0;
}
