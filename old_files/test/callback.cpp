/* callback.c - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macross.h"
#include "functions.h"
#include "interface.h"


extern MC_POPUP_MENU* create_popmenu(const MC_RECT* r);
extern void destroy_popmenu(MC_POPUP_MENU* m);

extern MaCrossView* getMainView(void);


static void DirtyRect(MaCrossView* view, const MC_RECT* r)
{
	update_rect(macross_view_additional_data(view), r->x, r->y, r->w, r->h);
}

static void SetTitle(MaCrossView* view, const char* title)
{
	set_title(macross_view_additional_data(view), title);
}

static void SetLocation(MaCrossView* view, const char* location)
{
}

static void focus(MaCrossView* view)
{
	on_focus(view);
}

static void notify_focus(MaCrossView* view, const MC_RECT* r)
{
}

static void killfocus(MaCrossView* view)
{
	on_lose_focus(view);
}

static void SetStatus(MaCrossView* view, const char* text)
{
}

static void update(MaCrossView* view)
{
	update_window(macross_view_additional_data(view));
}

static void ime_status(MC_BOOL b)
{
}

static void set_cursor(MC_CURSOR c)
{
	change_cursor((int)c);
}

static void error(int e, const char* url)
{
	fprintf(stderr, "error: %d :  %s \n", e, url);
}


static void context_menu(MaCrossView* view, const MC_CONTEXT_MENU_DATA* menu)
{
}

static int http_auth(const char* title, char* u, unsigned us, char* p, unsigned ps)
{
	return 0;
}

static void tooltip(MaCrossView* view, int x, int y, const char* text)
{
}

static int get_all_url(const char* url)
{
	return FALSE;
}

static int allow_request(const char* url)
{
	return TRUE;
}

static void loading_status(MaCrossView* view, unsigned p, MC_BOOL b)
{
}

MaCrossView* win_open(const char* url, unsigned int f, const MC_RECT* r)
{
	return 0;
}

void start_layout(MaCrossView* view)
{
}

MC_BOOL save_form(const char* l, const char* f, const char* u, const char* n, const char* v, MC_BOOL b)
{
	return TRUE;
}

void alert_box(MaCrossView* view, const char* msg)
{
}

MC_BOOL choose_file(char *utf8_file_name , unsigned int buffer_size, MC_BOOL is_save)
{
	return TRUE;
}

void init_callback(void)
{
	MC_CALLBACK_INFO info;
	memset(&info, 0, sizeof(MC_CALLBACK_INFO));

	info.cb_invalidate_rect = DirtyRect;
	info.cb_set_title       = SetTitle;
	info.cb_set_location    = SetLocation;
	info.cb_set_status		= SetStatus;
	info.cb_update_view_now = update;
	info.cb_set_ime_enable  = ime_status;
	info.cb_set_cursor		= set_cursor;
	info.cb_error   		= error;
	info.cb_context_menu	= context_menu;
	info.cb_provide_auth	= http_auth;
	info.cb_loading_progress = loading_status;
	info.cb_show_tooltip	= tooltip;
	info.cb_open_window		= win_open;
	info.cb_create_popup_menu = create_popmenu;
	info.cb_destroy_popup_menu = destroy_popmenu;
	info.cb_url_is_visited  = get_all_url;
	info.cb_save_submit_form = save_form;
	info.cb_alert_box = alert_box;
	info.cb_set_focus = focus;
	info.cb_change_focus = notify_focus;
	info.cb_kill_focus = killfocus;
	info.cb_start_layout = start_layout;
	info.cb_choose_file = choose_file;

	macross_set_callback(&info);
}
