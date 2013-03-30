/* interface - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "macross.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

MaCrossView* on_init(unsigned char* buffer, int width, int height, int pitch, void *data)
{
	MC_CONFIG c = {0};
	MaCrossView* v =  macross_view_create(buffer, width, height, pitch, data);	
	MC_SIZE lsize = {width, height};
	macross_view_set_minimum_layout_size(v, &lsize);

//	macross_get_config(&c);
//	c.scrollbar_width = 0;
//	macross_set_config(&c);
	
	return v;
}

void on_term(MaCrossView* view)
{
	macross_view_destroy(view);
}

void on_draw(MaCrossView* view, int x, int y, int width, int height)
{
	MC_RECT rc = {x, y, width, height};
	macross_view_update(view, 0);
}

void on_size(MaCrossView* view, unsigned char* buffer, int width, int height, int pitch)
{
	macross_view_resize(view, buffer, width, height, pitch);
}

void load_url(MaCrossView* view, const char* url)
{
	macross_view_open_url(view, url);
}

void on_key(MaCrossView* view, MC_KEY_EVENT_TYPE type, MC_VIRTUAL_KEY key, unsigned modifier)
{
	MC_KEY_EVENT k = {type, key, modifier};
	macross_keyboard_event(view, &k);
}

void on_mouse(MaCrossView* view, MC_MOUSE_EVENT_TYPE type, MC_MOUSE_BUTTON btn, int x, int y, unsigned modifier)
{
	MC_MOUSE_EVENT e = {type, btn, {x, y}, modifier};
	macross_mouse_event(view, &e);
}

void on_focus(MaCrossView* view)
{
	macross_view_set_focus(view);
}

void on_lose_focus(MaCrossView* view)
{
	macross_view_kill_focus(view);
}

void on_context_menu(MaCrossView* view, int x, int y, unsigned modifier)
{
	MC_CONTEXT_EVENT e = {{x, y}, modifier};	
	macross_context_menu_event(view, &e);
}

void on_chars(MaCrossView* view, const char* text)
{
	macross_view_input_text(view, text);
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
