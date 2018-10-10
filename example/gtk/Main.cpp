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
GtkWidget* drawArea = NULL;

MainApp* mainApp = NULL;

static VirtualKeyType get_virtual_key(int pk);

static void destroy(GtkWidget *widget, gpointer data)
{
    mainApp->onDestroy();
    delete mainApp;
    gtk_main_quit();
}

static gboolean expose(GtkWidget *widget, GdkEventExpose *event)
{
    mainApp->onDraw(WebRect(event->area.x, event->area.y, event->area.width, event->area.height));
    return FALSE;
}

static void size_change(GtkWidget *widget, GtkAllocation *allocation)
{
    int new_width = allocation->width;
    int new_height = allocation->height;

    if (new_width == width && new_height == height) {
        return;
    }

    width = new_width;
    height = new_height;

    if (width < 1) {
        width = 1;
    }
    if (height < 1) {
        height = 1;
    }

    mainApp->onResize(WebSize(width, height));
}

static gboolean key_press(GtkWidget *widget, GdkEventKey *event)
{
    unsigned int modifiers = 0;
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;
    if (event->state & (1 << 28))
        modifiers |= DF_ALT;

    mainApp->onKeyboardEvent(EVT_KEY_DOWN, get_virtual_key(event->keyval), modifiers);
    return FALSE;
}

static gboolean key_release(GtkWidget *widget, GdkEventKey *event)
{
    unsigned int modifiers = 0;
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;
    if (event->state & (1 << 28))
        modifiers |= DF_ALT;

    mainApp->onKeyboardEvent(EVT_KEY_UP, get_virtual_key(event->keyval), modifiers);
    return FALSE;
}

static gboolean focus_in(GtkWidget *widget, GdkEventFocus *event)
{
    mainApp->onFocusEvent(true);
    return FALSE;
}

static gboolean focus_out(GtkWidget *widget, GdkEventFocus *event)
{
    mainApp->onFocusEvent(false);
    return FALSE;
}

static gboolean mouse_button_press(GtkWidget *widget, GdkEventButton *event)
{
    MouseEventType type;
    MouseButtonType key = MOUSE_BTN_LEFT;
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
    if (event->state & (1 << 28))
        modifiers |= DF_ALT;

    mainApp->onMouseEvent(type, key, WebPoint((int)event->x, (int)event->y), modifiers);
    return FALSE;
}

static gboolean mouse_button_release(GtkWidget *widget, GdkEventButton *event)
{
    MouseEventType type;
    MouseButtonType key = MOUSE_BTN_LEFT;
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
    if (event->state & (1 << 28))
        modifiers |= DF_ALT;

    mainApp->onMouseEvent(type, key, WebPoint((int)event->x, (int)event->y), modifiers);
    return FALSE;
}

static gboolean mouse_motion_notify(GtkWidget *widget, GdkEventMotion *event)
{
    MouseButtonType key = MOUSE_BTN_LEFT;
    unsigned int modifiers = 0;
    if (event->state & 1)
        modifiers |= DF_SHIFT;
    if (event->state & 4)
        modifiers |= DF_CTRL;
    if (event->state & (1 << 28))
        modifiers |= DF_ALT;

    if (event->state & 256)
        key = MOUSE_BTN_LEFT;
    else if (event->state & 512)
        key = MOUSE_BTN_MIDDLE;
    else if (event->state & 1024)
        key = MOUSE_BTN_RIGHT;

    mainApp->onMouseEvent(EVT_MOUSE_MOVE, key, WebPoint((int)event->x, (int)event->y), modifiers);
    return FALSE;
}

int main(int argc, char* argv[])
{
    width = 800;
    height = 600;

    gtk_init(&argc, &argv);

    mainApp = new MainApp();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "davinci demo");

    drawArea = gtk_drawing_area_new();

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK (destroy), NULL);

    g_signal_connect (G_OBJECT(drawArea), "expose_event", G_CALLBACK (expose), NULL);

    g_signal_connect (G_OBJECT(window), "size_allocate", G_CALLBACK (size_change), NULL);

    g_signal_connect (G_OBJECT(window), "key_press_event", G_CALLBACK (key_press), NULL);

    g_signal_connect (G_OBJECT(window), "key_release_event", G_CALLBACK (key_release), NULL);

    g_signal_connect (G_OBJECT(window), "focus_in_event", G_CALLBACK (focus_in), NULL);

    g_signal_connect (G_OBJECT(window), "focus_out_event", G_CALLBACK (focus_out), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_BUTTON_PRESS_MASK);
    g_signal_connect (G_OBJECT(window), "button_press_event", G_CALLBACK (mouse_button_press), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_BUTTON_RELEASE_MASK);
    g_signal_connect (G_OBJECT(window), "button_release_event", G_CALLBACK (mouse_button_release), NULL);

    gtk_widget_add_events (GTK_WIDGET(window), GDK_POINTER_MOTION_MASK);
    g_signal_connect (G_OBJECT(window), "motion_notify_event", G_CALLBACK (mouse_motion_notify), NULL);

    gtk_container_add (GTK_CONTAINER (window), drawArea);

    gtk_widget_show(drawArea);
    gtk_widget_show(window);

    mainApp->onInit(WebSize(width, height));

    gtk_main();

    return 0;
}

typedef struct {
    VirtualKeyType vk;
    int pk;
}KeyEntities;

static KeyEntities key_map[] = {
    {KEY_BACK, GDK_BackSpace},
    {KEY_TAB, GDK_Tab},
    {KEY_CLEAR, GDK_Clear},
    {KEY_ENTER, GDK_Return},
    {KEY_SHIFT, GDK_Shift_L},
    {KEY_CTRL, GDK_Control_L},
    {KEY_ALT, GDK_Menu},
    {KEY_PAUSE, GDK_Pause},
    {KEY_CAPSLOCK, GDK_Caps_Lock},
    {KEY_ESCAPE, GDK_Escape},
    {KEY_SPACE, GDK_space},
    {KEY_PAGEUP, GDK_Prior},
    {KEY_PAGEDOWN, GDK_Next},
    {KEY_END, GDK_End},
    {KEY_HOME, GDK_Home},
    {KEY_LEFT, GDK_Left},
    {KEY_UP, GDK_Up},
    {KEY_RIGHT, GDK_Right},
    {KEY_DOWN, GDK_Down},
    {KEY_SELECT, GDK_Select},
    {KEY_PRINT, GDK_Print},
    {KEY_EXEC, GDK_Execute},
    {KEY_INSERT, GDK_Insert},
    {KEY_DELETE, GDK_Delete},
    {KEY_HELP, GDK_Help},
    {KEY_0, GDK_0},
    {KEY_1, GDK_1},
    {KEY_2, GDK_2},
    {KEY_3, GDK_3},
    {KEY_4, GDK_4},
    {KEY_5, GDK_5},
    {KEY_6, GDK_6},
    {KEY_7, GDK_7},
    {KEY_8, GDK_8},
    {KEY_9, GDK_9},
    {KEY_A, GDK_a},
    {KEY_B, GDK_b},
    {KEY_C, GDK_c},
    {KEY_D, GDK_d},
    {KEY_E, GDK_e},
    {KEY_F, GDK_f},
    {KEY_G, GDK_g},
    {KEY_H, GDK_h},
    {KEY_I, GDK_i},
    {KEY_J, GDK_j},
    {KEY_K, GDK_k},
    {KEY_L, GDK_l},
    {KEY_M, GDK_m},
    {KEY_N, GDK_n},
    {KEY_O, GDK_o},
    {KEY_P, GDK_p},
    {KEY_Q, GDK_q},
    {KEY_R, GDK_r},
    {KEY_S, GDK_s},
    {KEY_T, GDK_t},
    {KEY_U, GDK_u},
    {KEY_V, GDK_v},
    {KEY_W, GDK_w},
    {KEY_X, GDK_x},
    {KEY_Y, GDK_y},
    {KEY_Z, GDK_z},
    {KEY_LWIN, GDK_Meta_L},
    {KEY_RWIN, GDK_Meta_R},
    {KEY_EQUAL, GDK_equal},
    {KEY_MINUS, GDK_minus},
    {KEY_DECIMAL, GDK_decimalpoint},
    {KEY_SLASH, GDK_division},
    {KEY_F1, GDK_F1},
    {KEY_F2, GDK_F2},
    {KEY_F3, GDK_F3},
    {KEY_F4, GDK_F4},
    {KEY_F5, GDK_F5},
    {KEY_F6, GDK_F6},
    {KEY_F7, GDK_F7},
    {KEY_F8, GDK_F8},
    {KEY_F9, GDK_F9},
    {KEY_F10, GDK_F10},
    {KEY_F11, GDK_F11},
    {KEY_F12, GDK_F12},
    {KEY_F13, GDK_F13},
    {KEY_F14, GDK_F14},
    {KEY_F15, GDK_F15},
    {KEY_F16, GDK_F16},
    {KEY_F17, GDK_F17},
    {KEY_F18, GDK_F18},
    {KEY_F19, GDK_F19},
    {KEY_F20, GDK_F20},
    {KEY_F21, GDK_F21},
    {KEY_F22, GDK_F22},
    {KEY_F23, GDK_F23},
    {KEY_F24, GDK_F24},
    {KEY_SHIFT, GDK_Shift_L},
    {KEY_SHIFT, GDK_Shift_R},
    {KEY_CTRL, GDK_Control_L},
    {KEY_CTRL, GDK_Control_R},
};

static VirtualKeyType get_virtual_key(int pk)
{
    size_t i;
    for (i = 0; i < (sizeof(key_map)/sizeof(KeyEntities)); i++) {
        if (key_map[i].pk == pk) {
            return key_map[i].vk;
        }
    }
    return KEY_UNKNOWN; 
}
