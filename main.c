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

void ball_check_collision(Ball *ball, Paddle *paddle) {
    // Check if the ball's right edge intersects the paddle's left edge or vice versa
    if (ball->x + ball->radius >= paddle->x && ball->x - ball->radius <= paddle->x + paddle->width) {
        // Check if the ball's y-position is within the paddle's height range
        if (ball->y + ball->radius >= paddle->y && ball->y - ball->radius <= paddle->y + paddle->height) {
            // Reverse the ball's horizontal velocity to simulate bounce
            ball->vx = -ball->vx;
        }
    }
}

void ball_wall_collision(Ball *ball, float screen_height) {
    // Top wall collision
    if (ball->y - ball->radius <= 0) {
        ball->vy = -ball->vy; // Reverse vertical direction
    }
    // Bottom wall collision
    if (ball->y + ball->radius >= screen_height) {
        ball->vy = -ball->vy; // Reverse vertical direction
    }
}

void ball_update(Ball *ball) {
    ball->x += ball->vx;
    ball->y += ball->vy;
}

void reset_ball(Ball *ball, float screen_width, float screen_height) {
    ball->x = screen_width / 2;
    ball->y = screen_height / 2;
    ball->vx = (rand() % 2 == 0) ? 3 : -3;
    ball->vy = (rand() % 2 == 0) ? 4 : -4;
}

gboolean game_update(gpointer user_data) {
    GtkWidget *widget = GTK_WIDGET(user_data);

    ball_update(&ball); // Update the ball's position
    ball_check_collision(&ball, &paddle1); // Check collision with paddle1
    ball_check_collision(&ball, &paddle2); // Check collision with paddle2
    ball_wall_collision(&ball, 600); // Check collision with walls (assuming height is 600)

    // Check if the ball goes out of bounds (left or right) for scoring
    if (ball.x < 0 || ball.x > 800) { // Assuming screen width is 800
        reset_ball(&ball, 800, 600); // Reset ball to the center
    }

    gtk_widget_queue_draw(widget); // Redraw the screen
    return TRUE; // Continue the timer
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
    ball.vx = 3;
    ball.vy = 4;
    ball.radius = 10;

    // Create a drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area); // Add drawing area to the window
    g_signal_connect(drawing_area, "draw", G_CALLBACK(game_window_draw), NULL); // Connect draw signal
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL); // Connect key press signal

    g_timeout_add(16, game_update, drawing_area); // 16 ms for ~60 FPS

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
