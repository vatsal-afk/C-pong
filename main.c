#include <gtk/gtk.h>

#include "game_properties.h"

#include "ball.h"
#include "paddle.h"
#include "scoreboard.h"

Paddle paddle1, paddle2;
Ball ball;

void game_window_draw(GtkWidget *widget, cairo_t *cr) {
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0); // paddle 1
    cairo_rectangle(cr, paddle1.x, paddle1.y, paddle1.width, paddle1.height);
    cairo_fill(cr);

    cairo_rectangle(cr, paddle2.x, paddle2.y, paddle2.width, paddle2.height); // paddle 2
    cairo_fill(cr);

    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0); // ball
    cairo_arc(cr, ball.x, ball.y, ball.radius, 0, 2 * G_PI);
    cairo_fill(cr);
}

void ball_check_collision(Ball *ball, Paddle *paddle) {
    if (ball->x + ball->radius >= paddle->x && ball->x - ball->radius <= paddle->x + paddle->width) {
        if (ball->y + ball->radius >= paddle->y && ball->y - ball->radius <= paddle->y + paddle->height) {
            ball->vx = -ball->vx;
        }
    }
}

void ball_wall_collision(Ball *ball, float screen_height) {
    if (ball->y - ball->radius <= 0) { // top wall
        ball->vy = -ball->vy;
    }
    if (ball->y + ball->radius >= screen_height) { // bottom wall
        ball->vy = -ball->vy; 
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

    ball_update(&ball); 
    ball_check_collision(&ball, &paddle1); 
    ball_check_collision(&ball, &paddle2); 
    ball_wall_collision(&ball, 600); 
    // ISSUE!!! render screen height and width dynamically!!! else collision problem

    if (ball.x < 0 || ball.x > 800) { 
        reset_ball(&ball, 800, 600);
    }

    gtk_widget_queue_draw(widget); // redraw the screen
    return TRUE; // continue the timer
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Up) { // player 1
        paddle1.y -= paddle1.speed; // Move up
    } else if (event->keyval == GDK_KEY_Down) {
        paddle1.y += paddle1.speed; // Move down
    }
    if (paddle1.y < 0) { // bound check
        paddle1.y = 0; 
    } else if (paddle1.y > 600 - paddle1.height) {
        paddle1.y = 600 - paddle1.height; 
    }

    if (event->keyval == 119) { // player 2
        paddle2.y -= paddle2.speed; // Move up
    } else if (event->keyval == 115) { 
        paddle2.y += paddle2.speed; // Move down
    }
    if (paddle2.y < 0) { // bound check
        paddle2.y = 0; 
    } else if (paddle2.y > 600 - paddle2.height) {
        paddle2.y = 600 - paddle2.height; 
    }

    // redraw the window
    gtk_widget_queue_draw(widget);
    return TRUE;
}

void game_window_init(GtkWidget *window) {
    paddle1.x = 10;       
    paddle1.y = 250;      
    paddle1.width = 10;  
    paddle1.height = 100;
    paddle1.speed = 10;

    paddle2.x = 780;
    paddle2.y = 250;  
    paddle2.width = 10; 
    paddle2.height = 100;
    paddle2.speed = 10; 

    ball.x = 400;
    ball.y = 300;
    ball.vx = 3;
    ball.vy = 4;
    ball.radius = 10;

    // creating drawing area
    GtkWidget *drawing_area = gtk_drawing_area_new();

    gtk_container_add(GTK_CONTAINER(window), drawing_area); // add drawing area to the window

    g_signal_connect(drawing_area, "draw", G_CALLBACK(game_window_draw), NULL); // connect draw signal
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL); // connect key press signal

    g_timeout_add(16, game_update, drawing_area); // ~60 FPS

    gtk_widget_set_size_request(drawing_area, 800, 600); // size for drawing area

    gtk_widget_show_all(window); // show all widgets in the window
    gtk_widget_grab_focus(window); // the window has focus
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // main application window
    gtk_window_set_title(GTK_WINDOW(window), "virtual/C-pong");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // delete event
    
    game_window_init(window); // initialize game window

    gtk_main(); // gtk main loop
    
    return 0;
}
