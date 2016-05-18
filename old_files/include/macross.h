/**
 * \file macross.h
 * \author Zhang Ji Peng (onecoolx@gmail.com)
 * \date 2009/11/01
 * 
 * This file includes interfaces of macross browser.
 *
 \verbatim

    Copyright (C) 2009 ~ 2013 ZNCSoft .Inc

    All rights reserved.

    This file is part of MaCross web browser.

 \endverbatim
 */

#ifndef _MACROSS_H_
#define _MACROSS_H_

#include "mconfig.h"

#ifdef ENABLE_JSNATIVEBINDING
#include "JSBase.h"
#include "JSContextRef.h"
#include "JSStringRef.h"
#include "JSObjectRef.h"
#include "JSValueRef.h"
#include "JSBinding.h"
#endif

#if defined(WIN32) || defined(WINCE)
#ifdef DLL_EXPORT
#define MACROSS_API __declspec(dllexport)
#else
#define MACROSS_API __declspec(dllimport)
#endif
#else
#define MACROSS_API
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup macross MaCross functions and structures
 * @{
 */

/**
 * \typedef MC_BYTE
 * \brief byte data type (8 bit)
 */
typedef unsigned char MC_BYTE;

/**
 * \typedef MC_BOOL
 * \brief boolean type
 */
typedef int MC_BOOL;

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/**
 * \brief Maximum path length.
 */
#define MC_PATH_MAX  255

/**
 * \typedef MaCrossView
 * \brief An opaque type represents a webview object.
 */
typedef struct _mc_view MaCrossView;

/**
 * \brief Basic data type which stores a rectangle
 */
typedef struct _mc_rect {
	/** x coordinate in user space */
	int x;
	/** y coordinate in user space */
	int y;
	/** Rectangle width */
	int w;
	/** Rectanglw height */
	int h;
}MC_RECT;

/**
 * \brief Basic data type which stores a size
 */
typedef struct _mc_size {
	/** size width */
	int w;
	/** size height */
	int h;
}MC_SIZE;

/**
 * \brief Basic data type which stores a point
 */
typedef struct _mc_point {
	/** x coordinate in user space */
	int x;
	/** y coordinate in user space */
	int y;
}MC_POINT;

/**
 * \brief Pixel format of the screen buffer.
 */
typedef enum _mc_format {
	/** 
	 * 32bit per pixel BGRA format. (8888)
	 */
	PIXEL_FORMAT_BGRA32,	
	/** 
	 * 24bit per pixel BGR format.  (888) 
	 */
	PIXEL_FORMAT_BGR24,				
	/** 
	 * 16bit per pixel RGB format.  (565) 
	 */
	PIXEL_FORMAT_RGB16,			
}MC_PIXEL_FORMAT;

/**
 * \brief Status code return by functions.
 */
typedef enum _mc_status {
    /** 
     * The success status.
     */
	MC_STATUS_SUCCESS =  0,
    /** 
     * The failed status.
     */
	MC_STATUS_FAILED  = -1,
}MC_STATUS;

/**
 * \defgroup view Web View
 * @{
 */

/**
 * \fn MaCrossView* macross_view_create(MC_BYTE* buffer, int width, int height, int pitch, void *user_data)
 * \brief Create a new webview object with given data buffer.
 *
 * \param buffer    A Pointer to buffer for graphic output.
 * \param width     Webview width in pixels.
 * \param height    Webview height in pixels.
 * \param pitch     Width of the scanline in pixels.
 * \param user_data User's additional data.   
 *
 * \return 
 * 		- A new webview return on success.
 * 		- NULL return on failed.
 *
 * \sa macross_destroy_view, macross_view_update, macross_view_resize,
 * 	   macross_view_additional_data
 */
MACROSS_API MaCrossView* macross_view_create(MC_BYTE* buffer, int width, int height, int pitch, void *user_data);

/**
 * \fn void* macross_view_additional_data(MaCrossView* view)
 * \brief Return user additional data in web view.
 *
 * \param view  Pointer to an existing webview object.
 *
 * \return 
 * 		- additional data return on success.
 * 		- NULL return on failed.
 *
 * \sa macross_create_view, macross_view_update, macross_view_resize,
 *     macross_view_destroy
 */
MACROSS_API void* macross_view_additional_data(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_destroy(MaCrossView* view)
 * \brief Destroy a webview object.
 *
 * \param view  Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_create_view, macross_view_update, macross_view_resize,
 * 	   macross_view_additional_data
 */
MACROSS_API MC_STATUS macross_view_destroy(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_update(MaCrossView* view, const MC_RECT* rect)
 * \brief Update a rectangle on webview.
 *
 * \param view  Pointer to an existing webview object.
 * \param rect  Rectangle area for update, If NULL, all webview will be update.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_create_view, macross_view_destroy, macross_view_resize,
 * 	   macross_view_additional_data
 */
MACROSS_API MC_STATUS macross_view_update(MaCrossView* view, const MC_RECT* rect);

/**
 * \fn MC_STATUS macross_view_resize(MaCrossView* view, MC_BYTE* buffer, int width, int height, int pitch)
 * \brief Resize a webview with given parameters.
 *
 * \param view    Pointer to an existing webview object.
 * \param buffer  A Pointer to buffer for graphic output.
 * \param width   Webview width in pixels.
 * \param height  Webview height in pixels.
 * \param pitch   Width of the scanline in pixels.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_create, macross_destroy_view, macross_view_update,
 * 	   macross_view_additional_data
 */
MACROSS_API MC_STATUS macross_view_resize(MaCrossView* view, MC_BYTE* buffer, int width, int height, int pitch);

/**
 * \fn MC_STATUS macross_view_set_minimum_layout_size(MaCrossView* view, const MC_SIZE *size)
 * \brief Set or clear the minimum layout size for the web view.
 *
 * \param view    Pointer to an existing webview object.
 * \param size	  The minimum size of layout the wevview. NULL for clear the size limit, and the layout size
 *                will became the webview size.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_set_minimum_layout_size(MaCrossView* view, const MC_SIZE *size);

/**
 * \fn MC_STATUS macross_view_set_focus(MaCrossView* view)
 * \brief Set focus to a webview.
 *
 * \param view  Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_kill_focus
 */
MACROSS_API MC_STATUS macross_view_set_focus(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_kill_focus(MaCrossView* view)
 * \brief Kill focus from a webview.
 *
 * \param view  Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_set_focus
 */
MACROSS_API MC_STATUS macross_view_kill_focus(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_input_text(MaCrossView* view, const char* utf8_text)
 * \brief Input text into a webview, used by input method.
 *
 * \param view  	Pointer to an existing webview object.
 * \param utf8_text The text which is input with UTF-8 character encoding.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_set_focus
 */
MACROSS_API MC_STATUS macross_view_input_text(MaCrossView* view, const char* utf8_text);


/**
 * \brief Rendering mode for web page layout.
 * \sa macross_view_set_rendering_mode, macross_view_get_rendering_mode
 */
typedef enum _mc_render_mode {
	/**
	 * Layout the web page in original layout.
	 */
	MC_RENDERING_NORMAL,
	/**
	 * Layout the web page not needed for horizontal scrolling.
	 */
	MC_RENDERING_SMARTFIT,
}MC_RENDERING_MODE;

/**
 * \fn MC_STATUS macross_view_set_rendering_mode(MaCrossView* view, MC_RENDERING_MODE mode, int space)
 * \brief Set the specified rendering mode for web view.
 *
 * \param view  	Pointer to an existing webview object.
 * \param mode		The rendering mode to be set.
 * \param space		The layout width space for smart-fit mode.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * 	\sa macross_view_get_rendering_mode
 */
MACROSS_API MC_STATUS macross_view_set_rendering_mode(MaCrossView* view, MC_RENDERING_MODE mode, int space);

/**
 * \fn MC_STATUS macross_view_get_rendering_mode(MaCrossView* view, MC_RENDERING_MODE* mode)
 * 
 * \param view  	Pointer to an existing webview object.
 * \param mode		Pointer to a buffer to receiving the current rendering mode.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * 	\sa macross_view_set_rendering_mode
 */
MACROSS_API MC_STATUS macross_view_get_rendering_mode(MaCrossView* view, MC_RENDERING_MODE* mode);

/**
 * \fn MC_STATUS macross_view_set_scale_factor(MaCrossView* view, int precent)
 * 
 * \param view  	Pointer to an existing webview object.
 * \param precent   The scale precent of webview.(default 100)
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_get_scale_factor
 */
MACROSS_API MC_STATUS macross_view_set_scale_factor(MaCrossView* view, int precent);

/**
 * \fn MC_STATUS macross_view_get_scale_factor(MaCrossView* view, int* precent)
 * 
 * \param view  	Pointer to an existing webview object.
 * \param precent	Pointer to a buffer to receiving the scale precent.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_set_scale_factor
 */
MACROSS_API MC_STATUS macross_view_get_scale_factor(MaCrossView* view, int* precent);

/**
 * \fn MC_STATUS macross_view_set_view_source(MaCrossView* view, MC_BOOL enable)
 * \brief Set whether web view in view source mode.
 *
 * \param view  	Pointer to an existing webview object.
 * \param enable  	Whether enable view source mode or not. 
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_set_view_source(MaCrossView* view, MC_BOOL enable);

/**
 * \fn MC_STATUS macross_view_set_position(MaCrossView* view, int x, int y)
 * \brief Used to set the position of the page contents.
 *
 * \param view  Pointer to an existing webview object.
 * \param x     The x of the contents position.
 * \param y     The y of the contents position.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_get_position
 */
MACROSS_API MC_STATUS macross_view_set_position(MaCrossView* view, int x, int y);

/**
 * \fn MC_STATUS macross_view_get_position(MaCrossView* view, int* x, int* y)
 * \brief Get the position of the page contents.
 *
 * \param view  Pointer to an existing webview object.
 * \param x 	The Pointer to a buffer to receiving x of the contents position.
 * \param y 	The Pointer to a buffer to receiving y of the contents position.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_set_position
 */
MACROSS_API MC_STATUS macross_view_get_position(MaCrossView* view, int* x, int* y);

/**
 * \fn MC_STATUS macross_view_get_contents_size(MaCrossView* view, MC_SIZE* size)
 * \brief Get the size of the page contents.
 *
 * \param view  Pointer to an existing webview object.
 * \param size  The size of the contents.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_get_contents_size(MaCrossView* view, MC_SIZE* size);

/**
 * \fn MC_BOOL macross_view_search_text(MaCrossView* view, const char* utf8_str, 
 *     									MC_BOOL forward, MC_BOOL caseSensitive, MC_BOOL wrap)
 * \brief Searches a string in a web view and highlights the string if found.
 *
 * \param view  		Pointer to an existing webview object.
 * \param utf8_str 		The string to search for.
 * \param forward   	TRUE to search forward, FALSE to search backwards.
 * \param caseSensitive TRUE to for case-sensitive search, FALSE for case-insensitive search.
 * \param wrap 			TRUE to wrap around, FALSE to avoid wrapping.
 *
 * \return TRUE if found, FALSE if not found.
 *
 * \sa macross_view_mark_all_matches_text, macross_view_unmark_all_matches
 */
MACROSS_API MC_BOOL macross_view_search_text(MaCrossView* view, const char* utf8_str, 
												MC_BOOL forward, MC_BOOL caseSensitive, MC_BOOL wrap);
/**
 * \fn int macross_view_mark_all_matches_text(MaCrossView* view, const char *utf8_str, 
 *     							MC_BOOL caseSensitive, MC_BOOL highlight, unsigned int limit)
 * \brief Mark all matching strings in a web view and highlights the string or not.
 *
 * \param view  		Pointer to an existing webview object.
 * \param utf8_str 		The string to search for.
 * \param caseSensitive TRUE to for case-sensitive search, FALSE for case-insensitive search.
 * \param highlight 	TRUE to highlight, FALSE to unhighlight.
 * \param limit			The specified maching count. A limit of 0 means no limit.
 *
 * \return the matching count, -1 if no match.
 *
 * \sa macross_view_search_text, macross_view_unmark_all_matches
 */
MACROSS_API int macross_view_mark_all_matches_text(MaCrossView* view, const char *utf8_str, 
										MC_BOOL caseSensitive, MC_BOOL highlight, unsigned int limit);
/**
 * \fn MC_BOOL macross_view_unmark_all_matches(MaCrossView* view)
 * \brief Unmark all matching text in a document view.
 *
 * \param view  Pointer to an existing webview object.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_view_mark_all_matches_text, macross_view_search_text
 */
MACROSS_API MC_BOOL macross_view_unmark_all_matches(MaCrossView* view);

/**
 * \fn MC_BOOL macross_view_get_text_multiplier(MaCrossView* view, int *factor)
 * \brief Get the text size multiplier of the web view.
 *
 * \param view   Pointer to an existing webview object.
 * \param factor Pointer to a buffer receiving the text size multiplier. 
 * 				 Factor expresses int percent as an integer (eg 100 means 100 percent).
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_view_set_text_multiplier
 */
MACROSS_API MC_BOOL macross_view_get_text_multiplier(MaCrossView* view, int *factor);

/**
 * \fn MC_BOOL macross_view_set_text_multiplier(MaCrossView* view, int factor)
 * \brief Set the text size multiplier of the web view.
 *
 * \param view   Pointer to an existing webview object.
 * \param factor The specified text size multiplier. 
 * 				 Factor expresses int percent as an integer (eg 100 means 100 percent).
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_view_get_text_multiplier
 */
MACROSS_API MC_BOOL macross_view_set_text_multiplier(MaCrossView* view, int factor);

/**
 * \fn MC_BOOL macross_view_eval_script(MaCrossView* view, const char* urf8_script)
 * \brief Execute specified script for the web view.
 *
 * \param view  		Pointer to an existing webview object.
 * \param utf8_script	The specified script encoding with UTF-8 character encoding.
 *
 * \return TRUE on success, FALSE on error.
 */
MACROSS_API MC_BOOL macross_view_eval_script(MaCrossView* view, const char* urf8_script);
/** @} end of view*/


/**
 * \defgroup notify Notify
 * @{
 */

/**
 * \brief Cursor type for macross.
 * \sa cb_set_cursor
 */
typedef enum _mc_cursor {
	/** Normal pointer cursor */
    POINTER_CURSOR,
	/** Cross cursor */
    CROSS_CURSOR,
	/** Hand cursor */
    HAND_CURSOR,
	/** Move cursor */
    MOVE_CURSOR,
	/** Ibeam cursor */
    IBEAM_CURSOR,
	/** Wait cursor */
    WAIT_CURSOR,
	/** Help cursor */
    HELP_CURSOR,
	/** East resize cursor */
    EAST_CURSOR,
	/** North resize cursor */
    NORTH_CURSOR,
	/** North east resize cursor */
    NORTHEAST_CURSOR,
	/** North west resize cursor */
    NORTHWEST_CURSOR,
	/** South cursor */
    SOUTH_CURSOR,
	/** South east cursor */
    SOUTHEAST_CURSOR,
	/** South west cursor */
    SOUTHWEST_CURSOR,
	/** West cursor */
    WEST_CURSOR,
	/** North south cursor */
    NORTHSOUTH_CURSOR,
	/** East west cursor */
    EASTWEST_CURSOR,
	/** North east south west cursor */
    NORTHEASTSOUTHWEST_CURSOR,
	/** North west south east cursor */
    NORTHWESTSOUTHEAST_CURSOR,
	/** Column cursor */
    COLUMN_CURSOR,
	/** Row cursor */
    ROW_CURSOR,
	/** Vertical text cursor */
    VERTICALTEXT_CURSOR,
	/** Cell cursor */
    CELL_CURSOR,
	/** Context menu cursor */
    CONTEXTMENU_CURSOR,
	/** No drop cursor */
    NODROP_CURSOR,
	/** Not allowed cursor */
    NOTALLOWED_CURSOR,
	/** Progress cursor */
    PROGRESS_CURSOR,
	/** Alias cursor */
    ALIAS_CURSOR,
	/** Zoom in cursor */
    ZOOMIN_CURSOR,
	/** Zoom out cursor */
    ZOOMOUT_CURSOR,
	/** Copy cursor */
    COPY_CURSOR,
	/** None cursor */
    NONE_CURSOR,
}MC_CURSOR;

/** 
 * \brief Error code for macross. 
 * \sa cb_error
 */
typedef enum _mc_error {
    /** It's not error code, just as a base number for network error code.*/
    ERR_NET_BASE = 400000,
    /** The URL was not properly formatted. */
    ERR_NET_URL_ERROR = ERR_NET_BASE +1,
    /** The protocol was not supported. */
    ERR_NET_UNSUPPORTED_PROTOCOL,
    /** Couldn't resolve the host. */
    ERR_NET_DNS_ERROR,
    /** Failed to connect() to host or proxy. */
    ERR_NET_CONNECT_FAILED,
    /** It's an unknown network error.*/
    ERR_NET_UNKNOWN_ERROR,
    /** It's not error code, just as a base number for network HTTP error.*/
    ERR_NET_HTTP_BASE = ERR_NET_BASE +1000,
#if ENABLE_NATIVEERROR
    /** It's the same as the HTTP server response code 400. */
    ERR_NET_HTTP_400 = ERR_NET_HTTP_BASE +400,
    /** It's the same as the HTTP server response code 401. */
    ERR_NET_HTTP_401,
    /** It's the same as the HTTP server response code 402. */
    ERR_NET_HTTP_402,
    /** It's the same as the HTTP server response code 403. */
    ERR_NET_HTTP_403,
    /** It's the same as the HTTP server response code 404. */
    ERR_NET_HTTP_404,
    /** It's the same as the HTTP server response code 405. */
    ERR_NET_HTTP_405,
    /** It's the same as the HTTP server response code 406. */
    ERR_NET_HTTP_406,
    /** It's the same as the HTTP server response code 407. */
    ERR_NET_HTTP_407,
    /** It'sthe same as the HTTP server response code 408. */
    ERR_NET_HTTP_408,
    /** It's the same as the HTTP server response code 409. */
    ERR_NET_HTTP_409,
    /** It's the same as the HTTP server response code 410. */
    ERR_NET_HTTP_410,
    /** It's the same as the HTTP server response code 411. */
    ERR_NET_HTTP_411,
    /** It's the same as the HTTP server response code 412. */
    ERR_NET_HTTP_412,
    /** It's the same as the HTTP server response code 413. */
    ERR_NET_HTTP_413,
    /** It's the same as the HTTP server response code 414. */
    ERR_NET_HTTP_414,
    /** It's the same as the HTTP server response code 415. */
    ERR_NET_HTTP_415,
    /** It's the same as the HTTP server response code 416. */
    ERR_NET_HTTP_416,
    /** It's the same as the HTTP server response code 417. */
    ERR_NET_HTTP_417,
    /** It's the same as the HTTP server response code 500. */
    ERR_NET_HTTP_500 = ERR_NET_HTTP_BASE +500,
    /** It's the same as the HTTP server response code 501. */
    ERR_NET_HTTP_501,
    /** It's the same as the HTTP server response code 502. */
    ERR_NET_HTTP_502,
    /** It's the same as the HTTP server response code 503. */
    ERR_NET_HTTP_503,   
    /** It's the same as the HTTP server response code 504. */
    ERR_NET_HTTP_504,
    /** It's the same as the HTTP server response code 505. */
    ERR_NET_HTTP_505,
#endif
    /** It's not error code, just as a base number for network FTP error.*/
    ERR_NET_FTP_BASE = ERR_NET_BASE +2000,
    /** It's the same as the FTP server response code 421. */
    ERR_NET_FTP_421 = ERR_NET_FTP_BASE +421,
    /** It's the same as the FTP server response code 425. */
    ERR_NET_FTP_425 = ERR_NET_FTP_BASE +425,
    /** It's the same as the FTP server response code 426. */
    ERR_NET_FTP_426,
    /** It's the same as the FTP server response code 450. */
    ERR_NET_FTP_450 = ERR_NET_FTP_BASE +450,
    /** It's the same as the FTP server response code 451. */
    ERR_NET_FTP_451,
    /** It's the same as the FTP server response code 452. */
    ERR_NET_FTP_452,
    /** It's the same as the FTP server response code 500. */
    ERR_NET_FTP_500 = ERR_NET_FTP_BASE +500,
    /** It's the same as the FTP server response code 501. */
    ERR_NET_FTP_501,
    /** It's the same as the FTP server response code 502. */
    ERR_NET_FTP_502,
    /** It's the same as the FTP server response code 503. */
    ERR_NET_FTP_503,  
    /** It's the same as the FTP server response code 504. */
    ERR_NET_FTP_504,
    /** It's the same as the FTP server response code 530. */
    ERR_NET_FTP_530 = ERR_NET_FTP_BASE +530,
    /** It's the same as the FTP server response code 532. */
    ERR_NET_FTP_532 = ERR_NET_FTP_BASE +532,
    /** It's the same as the FTP server response code 550. */
    ERR_NET_FTP_550 = ERR_NET_FTP_BASE +550,
    /** It's the same as the FTP server response code 551. */
    ERR_NET_FTP_551,
    /** It's the same as the FTP server response code 552. */
    ERR_NET_FTP_552,
    /** It's the same as the FTP server response code 553. */
    ERR_NET_FTP_553,
    /** It's an unknown FTP error. */
    ERR_NET_FTP_UNKNOWN_ERROR = ERR_NET_FTP_BASE +900,
    /** It's not error code, just as a base number for network FILE error.*/
    ERR_NET_FILE_BASE = ERR_NET_BASE +3000,
    /** It's a FILE error. A file given with FILE:// couldn't be opened.*/
    ERR_NET_FILE_READ_ERROR = ERR_NET_FILE_BASE +1,
    /** It's not error code, just as a base number for network SSL error.*/
    ERR_NET_SSL_BASE = ERR_NET_BASE +4000,
    /** It's an SSL error which occurred somewhere in the SSL/TLS handshake. */
    ERR_NET_SSL_CONNECT_ERROR = ERR_NET_SSL_BASE +1,
    /** The remote server's SSL certificate was deemed not OK.*/
    ERR_NET_SSL_PEER_CERTIFICATE,
    /** The specified crypto engine wasn't found.*/
    ERR_NET_SSL_ENGINE_NOTFOUND,
    /** Failed setting the selected SSL crypto engine as default.*/
    ERR_NET_SSL_ENGINE_SETFAILED,
    /** Problem with the local client certificate.*/
    ERR_NET_SSL_CERTPROBLEM,
    /** Couldn't use specified cipher.*/
    ERR_NET_SSL_CIPHER,
    /** Peer certificate cannot be authenticated with known CA certificates.*/
    ERR_NET_SSL_CACERT,
    /** Requested FTP SSL level failed.*/
    ERR_NET_SSL_FTP_ERROR,
    /** Initiating the SSL Engine failed.*/
    ERR_NET_SSL_ENGINE_INITFAILED,
    /** Problem with reading the SSL CA cert (path? access rights?)*/
    ERR_NET_SSL_CACERT_BADFILE,
    /** It's not error code, just as a base number for network PROXY error.*/
    ERR_NET_PROXY_BASE = ERR_NET_BASE +5000,
    /** It's a PROXY error. */
    ERR_NET_PROXY_ERROR = ERR_NET_PROXY_BASE +1,
} MC_ERROR_CODE;

/**
 * \brief Context menu type.
 * \sa cb_context_menu
 */
typedef enum _mc_context_type {
	/** No special context menu. */
	MENU_TYPE_NONE 		= 0,
	/** Url link context menu. */
	MENU_TYPE_LINK 		= 1,
	/** Image context menu. */
	MENU_TYPE_IMAGE 	= 2,
	/** Selected text context menu. */
	MENU_TYPE_SELECT 	= 4,
	/** Editable text field context menu. */
	MENU_TYPE_EDIT		= 8,
}MC_CONTEXT_MENU_TYPE;

/**
 * \brief Create window flags.
 * \sa cb_open_window
 */
typedef enum _mc_window_flags {
	/** Tool bar */
	MC_TOOLBAR     = 0x01,
	/** Location bar */
	MC_LOCATIONBAR = 0x02,
	/** Menu bar */
	MC_MENUBAR     = 0x04,
	/** Status bar */
	MC_STATUSBAR   = 0x08,
	/** Scroll bars */
	MC_SCROLLBARS  = 0x10,
	/** Resizeable */
	MC_RESIZABLE   = 0x20,
	/** Modal dialog */
	MC_MODAL       = 0x40,
}MC_WINDOW_FLAGS;

/**
 * \brief Context menu data.
 * \sa cb_context_menu
 */
typedef struct _mc_context_data {
	/** Context menu type. */
	unsigned int           type;
	/** Menu populate location. */
	MC_POINT  	  	   location;
	/** Link url with UTF-8 encoding. */
	const char*   	   link_url;
	/** Image url with UTF-8 encoding. */
	const char*       image_url;
	/** Text with UTF-8 encoding. */
	const char*  	       text;
}MC_CONTEXT_MENU_DATA;

/**
 * \brief Popup menu
 * \sa cb_create_popup_menu, cb_destroy_popup_menu
 */
typedef struct _mc_popup_menu {
	/** Private handle. */
	void*    handle;
	/** Menu canvas buffer. */
	MC_BYTE* buffer;
	/** Bytes per scanline. */
	int      pitch;
	/** Popup menu area with webview. */
	MC_RECT  rect;
	/** Popup menu move callback function. */
	void (*move)(struct _mc_popup_menu* menu, const MC_RECT* rect);
	/** Popup menu show callback function. */
	void (*show)(struct _mc_popup_menu* menu);
	/** Popup menu hide callback function. */
	void (*hide)(struct _mc_popup_menu* menu);
	/** Popup menu capture callback function. */
	void (*capture)(struct _mc_popup_menu* menu);
	/** Popup menu dirty callback function. */
	void (*dirty)(struct _mc_popup_menu* menu, const MC_RECT* rect);
	/** Popup menu update callback function. */
	void (*update)(struct _mc_popup_menu* menu);
	/** User define data for popup menu. */
	void*    data;
}MC_POPUP_MENU;

/**
 * \brief The callback functions information structure, which contains notify callback functions. 
 */
typedef struct _mc_callback_t {
    /**
     * \fn void (*cb_invalidate_rect)(MaCrossView* view, const MC_RECT* rect)
     * \brief The callback function.
	 * 		   Which is used to notify update a rectangle area for a web view.
     *
     * \param view 	     The web view pointer.
     * \param rect		 The rectangle area needed to be update.
     *
     * \sa cb_update_view_now, cb_position_changed
     */
	void (*cb_invalidate_rect)(MaCrossView* view, const MC_RECT* rect);

    /**
     * \fn void (*cb_update_view_now)(MaCrossView* view)
     * \brief The callback function.
	 * 			Flush all the draw operation and update web view.
     *
     * \param view 	     The web view pointer.
     *
     * \sa cb_invalidate_rect, cb_position_changed
     */
	void (*cb_update_view_now)(MaCrossView* view);

	/**
	 * \fn void (*cb_position_changed)(MaCrossView* view, int ox, int oy, int nx, int ny)
	 * \brief The callback function.
	 * 			Which is used to notify the contents position changed.
	 *
     * \param view 	     The web view pointer.
	 * \param ox		 The old position X.
	 * \param oy		 The old position Y.
	 * \param nx		 The new position X.
	 * \param nx		 The new position Y.
	 *
	 * \sa cb_update_view_now, cb_invalidate_rect
	 */
	void (*cb_position_changed)(MaCrossView* view, int ox, int oy, int nx, int ny);

    /**
     * \fn void (*cb_set_title) (MaCrossView* view, const char* utf8_title)
     * \brief The callback function.
	 * 		   Which is used to set the browsing title of the Web page for the view.
     *
     * \param view 	     The web view pointer.
     * \param utf8_title The title of the browsing Web page with UTF-8 character encoding.
     *
     * \sa cb_set_location, cb_set_status
     */
	void (*cb_set_title)(MaCrossView* view, const char* utf8_title);

    /**
     * \fn void (*cb_set_location)(MaCrossView* view, const char* utf8_text)
     * \brief The callback function.
	 * 		   Which is used to set the visiting URL for location.
     *
     * \param view 	    	 The web view pointer.
     * \param utf8_location  The visiting URL with UTF-8 character encoding.
     *
     * \sa cb_set_location, cb_set_status, cb_loading_progress
     */
	void (*cb_set_location)(MaCrossView* view, const char* utf8_location);

    /**
     * \fn void (*cb_set_status)(MaCrossView* view, const char* utf8_text)
     * \brief The callback function.
	 * 		   Which is used to set status messages for the status bar.
     *
     * \param view 	     The web view pointer.
     * \param utf8_text  The visiting URL with UTF-8 character encoding.
     *
     * \sa cb_set_location, cb_set_title, cb_loading_progress
     */
	void (*cb_set_status)(MaCrossView* view, const char* utf8_text);

	/**
	 * \fn void (*cb_set_focus)(MaCrossView* view)
	 * \brief The callback function.
	 * 			Which is used to set focus for webview.
     *
     * \param view 	     The web view pointer.
	 *
	 * \sa cb_kill_focus, cb_change_focus
	 */
	void (*cb_set_focus)(MaCrossView* view);

	/**
	 * \fn void (*cb_kill_focus)(MaCrossView* view)
	 * \brief The callback function.
	 * 			Which is used to kill focus for webview.
     *
     * \param view 	     The web view pointer.
	 *
	 * \sa cb_set_focus, cb_change_focus
	 */
	void (*cb_kill_focus)(MaCrossView* view);

	/**
	 * \fn void (*cb_change_focus)(MaCrossView* view, const MC_RECT* rect)
	 * \brief The callback function.
	 * 			Which is used to notify new focus rectangle for wevview.
	 *
	 * \param view 		The web view pointer.
	 * \param rect		The new focus rectangle.
	 *
	 * \sa cb_set_focus, cb_kill_focus
	 */
	void (*cb_change_focus)(MaCrossView* view, const MC_RECT* rect);

	/**
	 * \fn void (*cb_start_layout)(MaCrossView* view)
	 * \brief The callback function.
	 * 			Which is used to notify first layout.
	 *
     * \param view 	     The web view pointer.
	 *
	 * \sa cb_set_location, cb_set_title, cb_set_status
	 */
	void (*cb_start_layout)(MaCrossView* view);

	/**
	 * \fn void (*cb_loading_status)(MaCrossView* view, unsigned int progress)
	 * \brief The callback function.
	 * 			Which is used to sign the loading progress.
	 *
	 * \param view      The web view pointer.
	 * \param progress  An estimate of the percent complete for a document load. 
	 * 	                 This value will range from 0 to 100.
	 * \param finish	The value that whether the loading is finished.
	 *
	 * \sa cb_set_location, cb_set_title, cb_set_status
	 */
	void (*cb_loading_progress)(MaCrossView* view, unsigned int progress, MC_BOOL finish);

    /**
     * \fn void (*cb_history_status)(MaCrossView* view, unsigned int back_count, unsigned int forward_count)
     * \brief The callback function. 
	 * 			Which is used to set history status.
     *
	 * \param view       	The web view pointer.
     * \param back_count 	The available backward list count.
     * \param forward_count The available forward list count.
     *
     * \sa cb_set_location, cb_set_title, cb_set_status
     */
    void (*cb_history_status)(MaCrossView* view, unsigned int back_count, unsigned int forward_count);

    /**
     * \fn void (*cb_show_tooltip)(MaCrossView* view, int x, int y, const char* utf8_text)
     * \brief The callback function.
	 * 			 which is used to show a tooltip.
     *
	 * \param view      The web view pointer.
     * \param x         The x position of tooltip in web view.
     * \param y         The y position of tooltip in web view.
     * \param utf8_text The tooltip message with UTF-8 character encoding. 
     */
	void (*cb_show_tooltip)(MaCrossView* view, int x, int y, const char* utf8_text);

    /**
     * \fn void (*cb_alert_box)(MaCrossView* view, const char* utf8_message)
     * \brief The callback function.
	 * 		   Which is used to Javascript alert() method.
     *
     * \param view 	    	 The web view pointer.
     * \param utf8_message	 The message text with UTF-8 encoding.
     *
     * \sa cb_confirm_box, cb_prompt_box
     */
	void (*cb_alert_box)(MaCrossView* view, const char* utf8_message);

    /**
     * \fn MC_BOOL (*cb_confirm_box)(MaCrossView* view, const char* utf8_text)
     * \brief The callback function.
	 * 		   Which is used to Javascript confirm() method.
     *
     * \param view 	     The web view pointer.
     * \param utf8_text	 The message text with UTF-8 encoding.
     *
     * \return TRUE if click "OK" button, otherwise FALSE.
	 *
     * \sa cb_alert_box, cb_prompt_box
     */
	MC_BOOL (*cb_confirm_box)(MaCrossView* view, const char* utf8_text);

    /**
     * \fn char *(*cb_prompt_box)(MaCrossView* view, const char*utf8_message , const char* utf8_default)
     * \brief The callback function.
	 * 		   Which is used to Javascript prompt() method.
     *
     * \param view 	     	The web view pointer.
     * \param utf8_message	The message text with UTF-8 encoding.
	 * \param utf8_default  The default text with UTF-8 encoding.
     *
     * \return Input text with UTF-8 encoding when commit, otherwise NULL.
	 *
     * \sa cb_alert_box, cb_confirm_box
     */
	char* (*cb_prompt_box)(MaCrossView* view, const char*utf8_message , const char* utf8_default);

	/**
	 * \fn void (*cb_context_menu)(MaCrossView* view, const MC_CONTEXT_MENU_DATA* nemu)
	 * \brief The callback function.
	 * 			Which is used to context menu populate.
	 *
     * \param view 	The web view pointer.
	 * \param menu  The context menu data.
	 */
	void (*cb_context_menu)(MaCrossView* view, const MC_CONTEXT_MENU_DATA* menu);

    /**
     * \fn MaCrossView* (*cb_open_window)(const char* utf8_url, unsigned int flags, const MC_RECT* rect)
     * \brief The callback function. 
	 * 			which is used to open a new window.
     *
     * \param utf8_url  The URL visited by this window, with encoding UTF-8.
     * \param flags     The window flags.
     * \param rect      The rectangle of this window. NULL for normal.
	 *
     * \return The new webview on success, NULL on failed.
     */
    MaCrossView* (*cb_open_window)(const char* utf8_url, unsigned int flags, const MC_RECT* rect);

    /**
     * \fn void (*cb_close_window)(MaCrossView* view)
     * \brief The callback function. 
	 * 			which is used to close the specified window.
     *
     * \param view 	The web view pointer.
     */
    void (*cb_close_window)(MaCrossView* view);

    /**
     * \fn MC_POPUP_MENU* (*cb_create_popup_menu)(const MC_RECT* rect)
     * \brief The callback function. 
	 * 			which is used to create a popup menu list.
     *
     * \param rect 	The rectangle area of popup menu list on the webview.
	 *
     * \return The new MC_POPUP_MENU object on success, NULL on failed.
     */
	MC_POPUP_MENU* (*cb_create_popup_menu)(const MC_RECT* rect);

    /**
     * \fn void (*cb_destroy_popup_menu)(MC_POPUP_MENU* menu)
     * \brief The callback function. 
	 * 			which is used to destroy the popup menu list.
     *
     * \param menu 	The MC_POPUP_MENU object pointer.
     */
	void (*cb_destroy_popup_menu)(MC_POPUP_MENU* menu);

	/**
	 * \fn MC_BOOL (*cb_provide_auth)(const char* utf8_title, char* username, unsigned int usize, 
	 *     															char* password, unsigned int psize)
	 * \brief The callback function.
	 *         Which is used to provide auth.
	 *
	 * \param utf8_title  The title of auth box with UTF-8 character encoding.
	 * \param username    Pointer to the buffer to receiving the username, encoding with UTF-8, '\0' terminal.
	 * \param usize       The buffer size of the username.
	 * \param password    Pointer to the buffer to receiving the password, encoding with UTF-8, '\0' terminal.
	 * \param psize       The buffer size of the password.
	 *
	 * \return True if user commit the auth, otherwise FALSE.
	 */
	MC_BOOL (*cb_provide_auth)(const char* utf8_title, char* username, unsigned int usize, 
																char* password, unsigned int psize);
	
    /**
     * \fn void (*cb_set_ime_enable)(MC_BOOL enable)
     * \brief The callback function.
	 * 		   Which is used to notify whether the input method is enable.
     *
     * \param enable  The boolean value set input method.
     */
	void (*cb_set_ime_enable)(MC_BOOL enable);

    /**
     * \fn void (*cb_set_cursor)(MC_CURSOR cur)
     * \brief The callback function.
	 * 		   Which is used to notify the cursor is changed.
     *
     * \param cursor  The current cursor.
     */
	void (*cb_set_cursor)(MC_CURSOR cursor);

    /**
     * \fn MC_BOOL (*cb_url_is_visited)(const char* utf8_url)
     * \brief The callback function.
	 * 		   Which is used to notify whether the url is visited.
     *
     * \param utf8_url  The URL will be tested which is UTF-8 character encoding.
     *
     * \return TRUE if url is visited, otherwise FALSE.
     */
	MC_BOOL (*cb_url_is_visited)(const char* utf8_url);

    /**
     * \fn MC_BOOL (*cb_allow_main_request)(const char* utf8_url)
     * \brief The callback function.
	 * 		   Which is used to notify whether the url is allowed request.
     *
     * \param utf8_url  The URL will be tested which is UTF-8 character encoding.
     *
     * \return TRUE if url is allowed to request, otherwise FALSE.
     */
	MC_BOOL (*cb_allow_main_request)(const char* utf8_url);

    /**
     * \fn void (*cb_error)(int err, const char * utf8_url)
     * \brief The callback function.
	 * 			Which is used to deal with error.
     *
     * \param err      The error code.
     * \param utf8_url The failed URL encoding with UTF-8.
     */
    void (*cb_error)(int err, const char * utf8_url);

    /**
     * \fn char* (*cb_user_agent_custom)(const char* utf8_url)
     * \brief The callback function. 
	 * 			Which is used to set User-Agent according to url.
     *
     * \param utf8_url The url with UTF-8 encoding for test.
	 *
     * \return The user defined User Agent encoded by UTF-8 for the url.
	 *         NULL for not define.
     */
	char* (*cb_user_agent_custom)(const char* utf8_url);

	/**
	 * \fn MC_BOOL (*cb_save_submit_form)(const char* base_url, const char* form_name, const char* utf8_url, 
	 * 											const char* name, const char* value, MC_BOOL is_end)
	 * \brief The callback function.
	 * 			Which is used to save submit form values for auto fill.
	 *
	 * \param base_url  The page base url.
	 * \param form_name The form name or id.
	 * \param utf8_url  The form action url.
	 * \param name      The form control name or id.
	 * \param value     The form control value.
	 * \param is_end    TRUE is is the last call, otherwise FALSE.  
	 * 
	 * \return TRUE if is process successed, otherwise FALSE.
	 */
	MC_BOOL (*cb_save_submit_form)(const char* base_url, const char* form_name, const char* utf8_url, 
												const char* name, const char* value, MC_BOOL is_end);

    /**
     * \fn MC_BOOL (*cb_choose_file)(char* utf8_file_name, unsigned int buffer_size, MC_BOOL is_save)
     * \brief The callback function.
	 * 			Which is used to create an open file dialog box or a save file dialog box.
     *
     * \param utf8_file_name  The pointer to the buffer receiving the full path name
	 * 						  of the file which selected by user.
     * \param buffer_size     The maximum length of the full path name of the file.
     * \param is_save         If FALSE, an open file dialog box is opened. 
	 * 						  Otherwise, a save file dialog box is opened.
     *
     * \return TRUE if users choose a file and click "OK" button, otherwise FALSE.
     */
    MC_BOOL (*cb_choose_file)(char* utf8_file_name, unsigned int buffer_size, MC_BOOL is_save);

    /**
     * \fn MC_BOOL (*cb_write_file_data)(int id, const char* utf8_url, const void* data,
	 *     								 unsigned long data_len, unsigned long total_len)
     * \brief The callback function.
	 * 			 which is used to deal with data stream. When MIME type is unsupported or 
	 * 			 content neet to be downloaded, users can decide whether saving data to a local file.
     *
     * \param id        The download job ID. Make a difference among the different downloading 
	 * 			        contents with the same URL.
     * \param utf8_url  The URL of the downloading reasource encoding with UTF-8.
     * \param data      The downloading data stream.
     * \param data_len  The size of the current downloading data.
     * \param total_len The total size of the data stream.
     *
     * \return TRUE if users want to continue downloading the data stream, otherwise FALSE.
     */
	MC_BOOL (*cb_write_file_data)(int id, const char* utf8_url, const void* data,
									 unsigned long data_len, unsigned long total_len);

    /**
     * \fn void (*cb_clipboard_set_data)(void* data, unsigned int data_len)
     * \brief The callback function.
	 * 			 which is used to set data to clipboard.
     *
     * \param data      The data which will be set to clipboard.
     * \param data_len  The length of the data.
     */
	void (*cb_clipboard_set_data)(void* data, unsigned int data_len);

    /**
     * \fn unsigned int (*cb_clipboard_data_len)(void)
     * \brief The callback function.
	 * 			 which is used to get the data length from the clipboard.
     */
	unsigned int (*cb_clipboard_data_len)(void);

    /**
     * \fn unsigned int (*cb_clipboard_get_data)(void* data_buffer, unsigned int buffer_len)
     * \brief The callback function.
	 * 			 which is used to get the data from the clipboard.
     *
     * \param data_buffer  Pointer to a buffer which to receiving the data.
     * \param buffer_len   The length of the buffer.
     */
	unsigned int (*cb_clipboard_get_data)(void* data_buffer, unsigned int buffer_len);
}MC_CALLBACK_INFO;

/**
 * \fn MC_STATUS macross_set_callback(const MC_CALLBACK_INFO* info)
 * \brief Set the notify callback functions.
 *
 * \param info The callback functions contains structure .
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_set_callback(const MC_CALLBACK_INFO* info);

/** @} end of notify*/



/**
 * \defgroup popmenu PopupMenu
 * @{
 */

/**
 * \fn MC_STATUS macross_menu_update(MC_POPUP_MENU* menu, const MC_RECT* rect)
 * \brief Update a rectangle on popup menu.
 *
 * \param menu  Pointer to an existing popup menu object.
 * \param rect  Rectangle area for update, If NULL, all popup menu will be update.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_menu_resize , macross_menu_hide, macross_menu_mouse_event,
 * 	   macross_menu_keyboard_event
 */
MACROSS_API MC_STATUS macross_menu_update(MC_POPUP_MENU* menu, const MC_RECT* rect);

/**
 * \fn MC_STATUS macross_menu_resize(MC_POPUP_MENU* menu, int width, int height)
 * \brief Resize a popup menu with given parameters.
 *
 * \param menu    Pointer to an existing popup menu object.
 * \param width   Popup menu width in pixels.
 * \param height  Popup menu height in pixels.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_menu_update, macross_menu_hide, macross_menu_mouse_event,
 * 	   macross_menu_keyboard_event
 */
MACROSS_API MC_STATUS macross_menu_resize(MC_POPUP_MENU* menu, int width, int height);

/**
 * \fn MC_STATUS macross_menu_hide(MC_POPUP_MENU* menu)
 * \brief Hide the popup menu.
 *
 * \param menu    Pointer to an existing popup menu object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_menu_update, macross_menu_resize, macross_menu_mouse_event,
 * 	   macross_menu_keyboard_event
 */
MACROSS_API MC_STATUS macross_menu_hide(MC_POPUP_MENU* menu);

/**
 * \fn MC_STATUS macross_menu_mouse_event(MC_POPUP_MENU* menu, const MC_MOUSE_EVENT* event)
 * \brief Process a mouse event for popup menu.
 *
 * \param menu 	Pointer to an existing popup menu object.
 * \param event	Pointer to a mouse event.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_menu_update, macross_menu_resize, macross_menu_hide,
 * 	   macross_menu_keyboard_event
 */
MACROSS_API MC_STATUS macross_menu_mouse_event(MC_POPUP_MENU* menu, const MC_MOUSE_EVENT* event);

/**
 * \fn MC_STATUS macross_menu_keyboard_event(MC_POPUP_MENU* menu, const MC_KEY_EVENT* event)
 * \brief Process a key board event for menu object.
 *
 * \param menu 	Pointer to an existing popup menu object.
 * \param event	Pointer to a key board event.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_menu_update, macross_menu_resize, macross_menu_hide,
 * 	   macross_menu_mouse_event
 */
MACROSS_API MC_STATUS macross_menu_keyboard_event(MC_POPUP_MENU* menu, const MC_KEY_EVENT* event);

/** @} end of popup menu*/

/**
 * \defgroup navigation Navigation
 * @{
 */

/**
 * \fn MC_STATUS macross_view_open_url(MaCrossView* view, const char* utf8_url)
 * \brief Open the specified url in a web view.
 *
 * \param view Pointer to an existing webview object.
 * \param utf8_url The specified URL encoding with UTF-8.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_open_url(MaCrossView* view, const char* utf8_url);

/**
 * \fn MC_STATUS macross_view_open_url_quietly(MaCrossView* view, const char* utf8_url)
 * \brief Open the specified url in a web view not record history.
 *
 * \param view Pointer to an existing webview object.
 * \param utf8_url The specified URL encoding with UTF-8.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_open_url_quietly(MaCrossView* view, const char* utf8_url);

/**
 * MC_STATUS macross_view_load_html(MaCrossView* view, const char* html_string, const char* utf8_refurl);
 *
 * \brief Load a html string to the web view.
 *
 * \param view		   Pointer to an existing webview object.
 * \param html_string  The html string encoding with UTF-8 to be loaded.
 * \param utf8_refurl  The reference URL encoding with UTF-8.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_load_html(MaCrossView* view, const char* html_string, const char* utf8_refurl);

/**
 * \fn MC_STATUS macross_view_forward(MaCrossView* view)
 * \brief Forward loading in a web view.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_forward(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_backward(MaCrossView* view)
 * \brief backward loading in a web view.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_backward(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_stop(MaCrossView* view)
 * \brief Stop loading in a web view.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_stop(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_reload(MaCrossView* view)
 * \brief Reload in a web view.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_reload(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_reflow(MaCrossView* view)
 * \brief Reformat the contents of the web view without reloading.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_reflow(MaCrossView* view);

/**
 * \fn MC_STATUS macross_view_repaint(MaCrossView* view)
 * \brief Repaint the contents of the web view without reloading and reflowing.
 *
 * \param view Pointer to an existing webview object.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_view_repaint(MaCrossView* view);
/** @} end of navigation*/

/**
 * \defgroup memctrl MemoryManager
 *
 */

/**
 * \fn MC_STATUS void macross_shrink_cache_memory(void)
 * \brief Shrink cache memory with MaCross used.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_shrink_cache_memory(void);

/**
 * \fn unsigned long macross_get_cache_memory_size(void)
 * \brief Get current cache memory size by bytes.
 *
 * \return cache size on success, 0 on error.
 */
MACROSS_API unsigned long macross_get_cache_memory_size(void);

/**
 * \fn unsigned long macross_set_disk_cache_size(unsigned long size)
 * \brief Set the maximum disk cache size in bytes. ( Default 16MB )
 *
 * \param size The disk cache size bigger than 0 in bytes.
 *
 * \return the old cache size, 0 on error.
 */
MACROSS_API unsigned long macross_set_disk_cache_size(unsigned long size);

/**
 * \fn MC_STATUS macross_clear_disk_cache(void)
 * \brief Clear all cached resources from disk.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_clear_disk_cache(void);

/**
 * \fn MC_STATUS macross_clear_cookies(void)
 * \brief Clear all cookies.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 */
MACROSS_API MC_STATUS macross_clear_cookies(void);
/** @} end of memory control*/

/**
 * \defgroup preferences Preferences
 * @{
 */

/**
 * \brief The proxy type.
 * \sa MC_PROXY
 */
typedef enum _mc_proxy_type {
    /** Http proxy. */
    PROXY_HTTP,
    /** Socks4 proxy. */
    PROXY_SOCKS4,
    /** Socks5 proxy. */
    PROXY_SOCKS5,
}MC_PROXY_TYPE;

/**
 * \brief Proxy information.
 * \sa MC_PROXY_TYPE
 */
typedef struct _mc_proxy {
	/** Proxy type, can be HTTP, SOCKET4 or SOCKET5. */
	MC_PROXY_TYPE  Type;
	/** Proxy ip address. */
	char* Host;
	/** Proxy port. */
	char* Port;
	/** User name encoding UTF-8 */
	char* UserName;
	/** User password*/
	char* PassWord;	
}MC_PROXY;

/**
 * \fn MC_BOOL macross_set_proxy(const MC_PROXY *proxy)
 * \brief Set the proxy server for network connection.
 *
 * \param proxy The proxy information, NULL for disable proxy.
 *
 * \return TRUE on success, FALSE on error.
 */
MACROSS_API MC_BOOL macross_set_proxy(const MC_PROXY* proxy);

/**
 * \fn MC_BOOL macross_set_certificate_dir(const char* utf8_path)
 * \brief Specify a certificate directory holding alternate certificates to verify with.
 *
 * \param utf8_path  The directory holding multiple CA certificates.
 *
 * \return TRUE on success, FALSE on error.
 */
MACROSS_API MC_BOOL macross_set_certificate_dir(const char* utf8_path);

/**
 * The preference information structure.
 *
 * \sa macross_set_config, macross_get_config
 */
#define FIELD_MAX   64
typedef struct _mc_config {
    /** Default language.  (en)*/
    char language[FIELD_MAX];
    /** Standard font. (Arial)*/
    char std_font[FIELD_MAX];
    /** Serif font. (Times New Roman)*/
    char serif_font[FIELD_MAX];
    /** Fixed font. (Courier New)*/
    char fixed_font[FIELD_MAX];
    /** Sans serif font. (Arial)*/
    char sans_serif_font[FIELD_MAX];
    /** Medium font size. (14)*/
    int fontsize;
    /** Medium fixed font size. (14)*/
    int fixed_fontsize;
    /** Scrollbar width. (16px)*/
    int scrollbar_width;
    /** Default encoding name. (iso8859-1)*/
    MC_ENCODING_NAME default_encoding;
    /** Is autodetect encoding. (TRUE)*/
    MC_BOOL autodetect_encoding;
    /** Is autoload images. (TRUE)*/
    MC_BOOL autoload_images;
    /** Is enable javascript. (TRUE)*/
    MC_BOOL enable_javascript;
    /** Is enable cookies. (TRUE)*/
    MC_BOOL enable_cookies;
    /** Is enable plugin. (TRUE)*/
    MC_BOOL enable_plugin;
    /** block popup window. (FALSE)*/
    MC_BOOL block_popup;
	/** show all at once. (FALSE)*/
	MC_BOOL show_at_once;
	/** Is text rendering antialias. (Win: FALSE, Other: TRUE)*/
	MC_BOOL text_antialias;
} MC_CONFIG;

/**
 * \fn MC_BOOL macross_get_config(MC_CONFIG *config)
 * \brief Get the current config information.
 *
 * \param config Pointer to a buffer receiving the current config information.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_set_config
 */
MACROSS_API MC_BOOL macross_get_config(MC_CONFIG *config);

/**
 * \fn MC_BOOL macross_set_config(const MC_CONFIG *config)
 * \brief Set the config information.
 *
 * \param config Pointer to the config information.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_get_config
 */
MACROSS_API MC_BOOL macross_set_config(const MC_CONFIG *config);

/** @} end of preferences*/

/**
 * \defgroup extension Extension
 * @{
 */
#if ENABLE_SCHEMEEXTENSION
/** 
 * \var typedef MC_BOOL (*cb_scheme_handler)(const char *utf8_url, void *data)
 * \brief The callback function of the scheme handler.
 *
 * \param utf8_url  The handled url with the specified scheme encoding with UTF-8.
 * \param data      The user data of the callback function.
 *
 * \return TRUE on success, otherwise FALSE.
 */
typedef MC_BOOL (*cb_scheme_callback)(const char *utf8_url, void *data);

/**
 * \fn MC_BOOL macross_register_scheme(const char * scheme, cb_scheme_callback cb, void* data)
 * \brief Register network protocol scheme handler.
 *
 * \param scheme The scheme of protocol.
 * \param cb The callback of the scheme handler.
 * \param data The parameter of the callback function.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_unregister_scheme
 */
MACROSS_API MC_BOOL macross_register_scheme(const char * scheme, cb_scheme_callback cb, void* data);

/**
 * \fn MC_BOOL macross_unregister_scheme(const char* scheme)
 * \brief Unregister network protocol scheme handler.
 *
 * \param scheme The scheme of protocol.
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_register_scheme
 */
MACROSS_API MC_BOOL macross_unregister_scheme(const char* scheme);
#endif

#ifdef ENABLE_JSNATIVEBINDING
/**
 * \fn MC_BOOL macross_js_define_class(JSNativeClass *jclass)
 * \brief Define a javascript native binding class.
 *
 * \param jclass The description of the javascript class.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_js_undefine_class
 */
MACROSS_API MC_BOOL macross_js_define_class(JSNativeClass* jclass);

/**
 * \fn MC_BOOL macross_js_undefine_class(JSNativeClass* jclass)
 * \brief Undefine a javascript native binding class.
 *
 * \param jclass The description of the javascript class.
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_js_define_class
 */
MACROSS_API MC_BOOL macross_js_undefine_class(JSNativeClass* jclass);

/**
 * \fn const JSClassRef macross_js_lookup_class(const char* utf8_name)
 * \brief search a javascript native binding with the class name.
 *
 * \param utf8_name The name of the native class.
 *
 * \return JSClassRef on success, NULL on error.
 */
MACROSS_API const JSClassRef macross_js_lookup_class(const char* utf8_name);

/**
 * \fn MC_BOOL macross_js_define_function(JSNativeFunction *func)
 * \brief Define a javascript native binding function.
 *
 * \param func The description of the Native Function 
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_js_undefine_function
 */
MACROSS_API MC_BOOL macross_js_define_function(JSNativeFunction *func);

/**
 * \fn MC_BOOL macross_js_undefine_function(JSNativeFunction *func)
 * \brief Undefine a javascript native binding function.
 *
 * \param func The description of the Native Function 
 *
 * \return TRUE on success, FALSE on error.
 *
 * \sa macross_js_define_function
 */
MACROSS_API MC_BOOL macross_js_undefine_function(JSNativeFunction *func);
#endif

/**
 * \brief Http method for request.
 */
typedef enum _req_type {
	/**
	 * Http GET method.
	 */
	REQUEST_GET,
	/**
	 * Http Post method.
	 */
	REQUEST_POST,
}MC_REQUEST_TYPE;

/**
 * \var typedef MC_BOOL (*cb_network_callback)(unsigned int code, unsigned char* data, unsigned int len, MC_BOOL finish)
 * \brief The callback function of the received http response data.
 *
 * \param code 	The http status code.
 * \param data  The data return from http request.
 * \param len   The data length.
 * \param finish Whether the data is finish.
 *
 * \return TRUE for continue received data, otherwise FALSE.
 */
typedef MC_BOOL (*cb_network_callback)(unsigned int code, unsigned char* data, unsigned int len, MC_BOOL finish);

/**
 * \brief Http response code.
 */
typedef enum _resp_code {
	/**
	 * Request is a invalid url.
	 */
	RESPONSE_INVALID_URL = 0,
	/**
	 * Http return 200, is OK.
	 */
	RESPONSE_OK 		 = 200,
	/**
	 * Http return a error.
	 */
	RESPONSE_ERROR 		 = 999,
}MC_RESPONSE;

/**
 * \fn MC_RESPONSE macross_network_request(MC_REQUEST_TYPE type, const char* utf8_url, 
 * 															cb_network_callback cb, unsigned int timeout)
 * \brief Send a http request with specified url and query.
 *
 * \param type  	The http request method type.
 * \param utf8_url  The URL which request with query.
 * \param cb		The callback for received response data, can be NULL.
 * \param timeout   The timeout for request in seconds. (5 ~ 300)
 *
 * \return The response code for the http request.
 */
MACROSS_API MC_RESPONSE macross_network_request(MC_REQUEST_TYPE type, const char* utf8_url, 
															cb_network_callback cb, unsigned int timeout);

/** @} end of extension*/

/**
 * \defgroup loop Main loop
 * @{
 */

/**
 * \fn MC_STATUS macross_initialize(MC_PIXEL_FORMAT format, int screen_width, int screen_height)
 * \brief Initializes the MaCross with the specified color format.
 *
 * \param format 		The pixel format of macross.
 * \param screen_width	The screen width.
 * \param screen_height The screen height.
 *
 * \return 
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_shutdown
 */
MACROSS_API MC_STATUS macross_initialize(MC_PIXEL_FORMAT format, int screen_width, int screen_height);

/**
 * \fn void macross_shutdown(void)
 * \brief Shutdown the MaCross. 
 *        Should be called when MaCross will not be used anymore.
 *
 * \sa macross_initialize
 */
MACROSS_API void macross_shutdown(void);

/**
 * \fn void macross_event_dispatch(MC_DISPATCH_TYPE type)
 * \brief MaCross events main loop.
 *
 * \sa MC_DISPATCH_TYPE
 */
MACROSS_API void macross_event_dispatch(void);

/** @} end of event loop*/
/** @} end of macross*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_MACROSS_H_*/
