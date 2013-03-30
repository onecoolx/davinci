/*
** webcallback.cpp: webcallback implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "macross.h"

#include "WebCallback.h"

namespace MaCross {

void (*cb_invalidate_rect)(_mc_view*, const _mc_rect*);
void (*cb_update_view_now)(_mc_view*);
void (*cb_position_changed)(_mc_view*, int, int, int, int);

void (*cb_set_title)(_mc_view*, const char*);
void (*cb_set_location)(_mc_view*, const char*);
void (*cb_set_status)(_mc_view*, const char*);

void (*cb_set_focus)(_mc_view*);
void (*cb_kill_focus)(_mc_view*);
void (*cb_change_focus)(_mc_view*, const _mc_rect*);

void (*cb_start_layout)(_mc_view*);

void (*cb_alert_box)(_mc_view*, const char*);
int  (*cb_confirm_box)(_mc_view*, const char*);
char* (*cb_prompt_box)(_mc_view*, const char* , const char*);
void (*cb_context_menu)(_mc_view*, const _mc_context_data*);
int (*cb_provide_auth)(const char*, char *, unsigned int, char *, unsigned int);
void (*cb_loading_progress)(_mc_view*, unsigned int, int);
void (*cb_history_status)(_mc_view*, unsigned int, unsigned int);
void (*cb_show_tooltip)(_mc_view*, int, int, const char*);

_mc_view* (*cb_open_window)(const char*, unsigned int, const _mc_rect*);
void (*cb_close_window)(_mc_view*);

_mc_popup_menu* (*cb_create_popup_menu)(const _mc_rect*);
void (*cb_destroy_popup_menu)(_mc_popup_menu*);

void (*cb_set_cursor)(_mc_cursor);
void (*cb_set_ime_enable)(int);
int (*cb_url_is_visited)(const char*);
int (*cb_allow_main_request)(const char*);
void (*cb_error)(int, const char*);
int (*cb_choose_file)(char*, unsigned int, int);
char* (*cb_user_agent_custom)(const char*);

int (*cb_save_submit_form)(const char*, const char*, const char*, const char*, const char*, int);

int (*cb_write_file_data)(int, const char*, const void*, unsigned long, unsigned long);

void (*cb_clipboard_set_data)(void*, unsigned int);
unsigned int (*cb_clipboard_data_len)(void);
unsigned int (*cb_clipboard_get_data)(void*, unsigned int);

void _init_callback(void)
{
	cb_invalidate_rect		 = 0;
	cb_update_view_now		 = 0;
	cb_position_changed 	 = 0;
	cb_set_title			 = 0;
	cb_set_location			 = 0;
	cb_set_status			 = 0;
	cb_set_focus			 = 0;
	cb_kill_focus			 = 0;
	cb_change_focus			 = 0;
	cb_start_layout			 = 0;
	cb_alert_box			 = 0;
	cb_confirm_box			 = 0;
	cb_prompt_box			 = 0;
	cb_context_menu			 = 0;
	cb_open_window			 = 0;
	cb_close_window			 = 0;
	cb_create_popup_menu	 = 0;
	cb_destroy_popup_menu	 = 0;
	cb_provide_auth			 = 0;
	cb_loading_progress		 = 0;
	cb_history_status		 = 0;
	cb_show_tooltip			 = 0;
	cb_set_cursor			 = 0;
	cb_set_ime_enable		 = 0;
	cb_url_is_visited		 = 0;
	cb_allow_main_request	 = 0;
	cb_error				 = 0;
	cb_choose_file			 = 0;
	cb_user_agent_custom	 = 0;
	cb_save_submit_form		 = 0;
	cb_write_file_data		 = 0;
	cb_clipboard_set_data	 = 0;
	cb_clipboard_data_len	 = 0;
	cb_clipboard_get_data	 = 0;
}

void _set_callback(const _mc_callback_t* cb)
{
	cb_invalidate_rect		 = cb->cb_invalidate_rect;
	cb_update_view_now		 = cb->cb_update_view_now;
	cb_position_changed 	 = cb->cb_position_changed;
	cb_set_title			 = cb->cb_set_title;
	cb_set_location			 = cb->cb_set_location;
	cb_set_status			 = cb->cb_set_status;
	cb_set_focus			 = cb->cb_set_focus;
	cb_kill_focus			 = cb->cb_kill_focus;
	cb_change_focus			 = cb->cb_change_focus;
	cb_start_layout			 = cb->cb_start_layout;
	cb_alert_box			 = cb->cb_alert_box;
	cb_confirm_box			 = cb->cb_confirm_box;
	cb_prompt_box			 = cb->cb_prompt_box;
	cb_context_menu			 = cb->cb_context_menu;
	cb_open_window			 = cb->cb_open_window;
	cb_close_window			 = cb->cb_close_window;
	cb_create_popup_menu	 = cb->cb_create_popup_menu;
	cb_destroy_popup_menu	 = cb->cb_destroy_popup_menu;
	cb_provide_auth			 = cb->cb_provide_auth;
	cb_loading_progress		 = cb->cb_loading_progress;
	cb_history_status		 = cb->cb_history_status;
	cb_show_tooltip			 = cb->cb_show_tooltip;
	cb_set_cursor			 = cb->cb_set_cursor;
	cb_set_ime_enable		 = cb->cb_set_ime_enable;
	cb_url_is_visited		 = cb->cb_url_is_visited;
	cb_allow_main_request	 = cb->cb_allow_main_request;
	cb_error				 = cb->cb_error;
	cb_choose_file			 = cb->cb_choose_file;
	cb_user_agent_custom	 = cb->cb_user_agent_custom;
	cb_save_submit_form		 = cb->cb_save_submit_form;
	cb_write_file_data		 = cb->cb_write_file_data;
	cb_clipboard_set_data	 = cb->cb_clipboard_set_data;
	cb_clipboard_data_len	 = cb->cb_clipboard_data_len;
	cb_clipboard_get_data	 = cb->cb_clipboard_get_data;
}

}
