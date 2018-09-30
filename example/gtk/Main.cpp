/*
 * MainApp.h: Cross platform application framework.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "../MainApp.h"

static int width = 0;
static int height = 0;

GtkWidget* window = NULL;
GtkWidget* drawarea = NULL;

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static gboolean expose(GtkWidget *widget, GdkEventExpose *event)
{
    return FALSE;
}

static void size_change(GtkWidget *widget, GtkAllocation *allocation)
{
    width = allocation->width;
    height = allocation->height;

    if (width < 1)
        width = 1;
    if (height < 1)
        height = 1;
}

static gboolean key_press(GtkWidget *widget, GdkEventKey *event)
{
    return FALSE;
}

static gboolean key_release(GtkWidget *widget, GdkEventKey *event)
{
    return FALSE;
}

static gboolean mouse_button_press(GtkWidget *widget, GdkEventButton *event)
{
    MouseEventType type;
    unsigned int key = 0;
    unsigned int modifiers = 0;
    switch(event->button){
        case 1:
            type = EVT_MOUSE_DOWN;
            key = MOUSE_BTN_LEFT;
            break;
        case 2:
            type = EVT_MOUSE_DOWN;
            key = MOUSE_BTN_MIDDLE;
            break;
        case 3:
            type = EVT_MOUSE_DOWN;
            key = MOUSE_BTN_RIGHT;
            break;
    }
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;
    //FIXME: 

    return FALSE;
}

static gboolean mouse_button_release(GtkWidget *widget, GdkEventButton *event)
{
    MouseEventType type;
    unsigned int key = 0;
    unsigned int modifiers = 0;
    switch(event->button){
        case 1:
            type = EVT_MOUSE_UP;
            key = MOUSE_BTN_LEFT;
            break;
        case 2:
            type = EVT_MOUSE_UP;
            key = MOUSE_BTN_MIDDLE;
            break;
        case 3:
            type = EVT_MOUSE_UP;
            key = MOUSE_BTN_RIGHT;
            break;
    }
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;
    // FIXME:

    return FALSE;
}

static gboolean mouse_motion_notify(GtkWidget *widget, GdkEventMotion *event)
{
    unsigned int key = 0;
    unsigned int modifiers = 0;
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;

    if (event->state & 256)
        key = MOUSE_BTN_LEFT;
    else if (event->state & 512)
        key = MOUSE_BTN_MIDDLE;
    else if (event->state & 1024)
        key = MOUSE_BTN_RIGHT;
    // FIXME:

    return FALSE;
}

int main(int argc, char* argv[])
{
    width = 800;
    height = 600;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "davinci demo");

    drawarea = gtk_drawing_area_new();

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK (destroy), NULL);

    g_signal_connect (G_OBJECT(drawarea), "expose_event", G_CALLBACK (expose), NULL);

    g_signal_connect (G_OBJECT(window), "size_allocate", G_CALLBACK (size_change), NULL);

    g_signal_connect (G_OBJECT(window), "key_press_event", G_CALLBACK (key_press), NULL);

    g_signal_connect (G_OBJECT(window), "key_release_event", G_CALLBACK (key_release), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_BUTTON_PRESS_MASK);
    g_signal_connect (G_OBJECT(window), "button_press_event", G_CALLBACK (mouse_button_press), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_BUTTON_RELEASE_MASK);
    g_signal_connect (G_OBJECT(window), "button_release_event", G_CALLBACK (mouse_button_release), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_POINTER_MOTION_MASK);
    g_signal_connect (G_OBJECT(window), "motion_notify_event", G_CALLBACK (mouse_motion_notify), NULL);

    gtk_container_add (GTK_CONTAINER (window), drawarea);

    gtk_widget_show(drawarea);
    gtk_widget_show(window);

    gtk_main();

    return 0;
}
