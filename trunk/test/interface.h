/* interface - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "macross.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*web view*/
MaCrossView* on_init(unsigned char* buffer, int width, int height, int pitch, void* data);

void on_term(MaCrossView* view);

void on_draw(MaCrossView* view, int x, int y, int width, int height);

void on_size(MaCrossView* view, unsigned char* buffer, int width, int height, int pitch);

/*event*/
void on_mouse(MaCrossView* view, MC_MOUSE_EVENT_TYPE type, MC_MOUSE_BUTTON btn, int x, int y, unsigned modifier);

void on_context_menu(MaCrossView* view, int x, int y, unsigned modifier);

void on_key(MaCrossView* view, MC_KEY_EVENT_TYPE type, MC_VIRTUAL_KEY key, unsigned modifier);

void on_chars(MaCrossView* view, const char* text);

void on_focus(MaCrossView* view);

void on_lose_focus(MaCrossView* view);

/*page*/
void load_url(MaCrossView* view, const char* url);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif/* _INTERFACE_H_ */
