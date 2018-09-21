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

GdkPixbuf* pixbuf = NULL;


int main(int argc, char* argv[])
{
    return 0;
}
