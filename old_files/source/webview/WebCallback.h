/*
** webcallback.h: webcallback implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#ifndef _WEBCALLBACK_H_
#define _WEBCALLBACK_H_

#include "macross.h"

namespace MaCross {

extern void (*cb_invalidate_rect)(_mc_view*, const _mc_rect*);
extern void (*cb_update_view_now)(_mc_view*);
extern void (*cb_position_changed)(_mc_view*, int, int, int, int);

extern void (*cb_alert_box)(_mc_view*, const char*);
extern int  (*cb_confirm_box)(_mc_view*, const char*);
extern char* (*cb_prompt_box)(_mc_view*, const char* , const char*);

extern void (*cb_context_menu)(_mc_view*, const _mc_context_data*);

extern int (*cb_provide_auth)(const char*, char*, unsigned int, char*, unsigned int);

extern void (*cb_loading_progress)(_mc_view*, unsigned int, int);

extern void (*cb_history_status)(_mc_view*, unsigned int, unsigned int);

extern void (*cb_show_tooltip)(_mc_view*, int, int, const char*);

extern void (*cb_set_title)(_mc_view*, const char*);
extern void (*cb_set_location)(_mc_view*, const char*);
extern void (*cb_set_status)(_mc_view*, const char*);

extern void (*cb_set_focus)(_mc_view*);
extern void (*cb_kill_focus)(_mc_view*);
extern void (*cb_change_focus)(_mc_view*, const _mc_rect*);

extern void (*cb_start_layout)(_mc_view*);

extern _mc_view* (*cb_open_window)(const char*, unsigned int, const _mc_rect*);
extern void (*cb_close_window)(_mc_view*);

extern void (*cb_set_cursor)(_mc_cursor cursor);
extern void (*cb_set_ime_enable)(int);
extern int (*cb_url_is_visited)(const char*);
extern int (*cb_allow_main_request)(const char*);
extern void (*cb_error)(int, const char*);
extern int (*cb_choose_file)(char*, unsigned int, int);
extern char* (*cb_user_agent_custom)(const char*);
extern int (*cb_save_submit_form)(const char*, const char*, const char*, const char*, const char*, int);

extern _mc_popup_menu* (*cb_create_popup_menu)(const _mc_rect*);
extern void (*cb_destroy_popup_menu)(_mc_popup_menu*);

extern int (*cb_write_file_data)(int, const char*, const void*, unsigned long, unsigned long);

extern void (*cb_clipboard_set_data)(void*, unsigned int);
extern unsigned int (*cb_clipboard_data_len)(void);
extern unsigned int (*cb_clipboard_get_data)(void*, unsigned int);

void _init_callback(void);
void _set_callback(const _mc_callback_t*);
}
#endif/*_WEBCALLBACK_H_*/
