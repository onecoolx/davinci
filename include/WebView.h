/*
 * WebView.h: WebView implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_WEBVIEW_H_
#define _DAVINCI_WEBVIEW_H_

namespace davinci {

/**
 * \defgroup content WebView
 * @{
 */

class EXPORT_API WebView : public WebObject
{
};

#if 0
/**
 * \fn MC_STATUS macross_mouse_event(MaCrossView* view, const MC_MOUSE_EVENT *event) 
 * \brief Process a mouse event for web view.
 *
 * \param view 	Pointer to an existing webview object.
 * \param event	Pointer to a mouse event.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_keyboard_event, macross_context_menu_event
 */
MACROSS_API MC_STATUS macross_mouse_event(MaCrossView* view, const MC_MOUSE_EVENT *event);
/**
 * \fn MC_STATUS macross_keyboard_event(MaCrossView* view, const MC_KEY_EVENT *event)
 * \brief Process a key board event for web view.
 *
 * \param view 	Pointer to an existing webview object.
 * \param event	Pointer to a key board event.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_mouse_event, macross_context_menu_event
 */
MACROSS_API MC_STATUS macross_keyboard_event(MaCrossView* view, const MC_KEY_EVENT *event);
/**
 * \fn MC_STATUS macross_context_menu_event(MaCrossView* view, const MC_CONTEXT_EVENT *event)
 * \brief Process a context menu event for web view.
 *
 * \param view 	Pointer to an existing webview object.
 * \param event	Pointer to a context menu event.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_mouse_event, macross_keyboard_event
 */
MACROSS_API MC_STATUS macross_context_menu_event(MaCrossView* view, const MC_CONTEXT_EVENT *event);
#endif

/** @} end of content*/
} /* namespace davinci */

#endif /*_DAVINCI_WEBVIEW_H_*/
