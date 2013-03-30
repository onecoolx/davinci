/* functions - MaCross application 
 * 
 * Copyright (C) 2009 Zhang Ji Peng
 * Contact: onecoolx@gmail.com
 */

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void update_rect(void *p, int x, int y, int w, int h);

void update_window(void *p);

void set_title(void *p, const char* text);

void change_cursor(int c);

MaCrossView* window_open(const char* url, int x, int y, int w, int h);

unsigned int set_timer(unsigned int mscend, void(*func)(void*), void* data);

void kill_timer(unsigned int id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_FUNCTIONS_H_*/
