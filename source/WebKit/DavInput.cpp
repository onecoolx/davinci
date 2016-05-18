
#if 0
/**
 * \brief Mouse event structure.
 * \sa MC_KEY_EVENT, MC_CONTEXT_EVENT
 */
typedef struct _mc_mouse_evt {
	/**
 	 * Mouse event type.
 	 */
	MC_MOUSE_EVENT_TYPE type;
	/**
	 * Mouse button type.
	 */
	MC_MOUSE_BUTTON   button;
	/**
	 * Mouse event point.
	 */
	MC_POINT      	   point;
	/**
	 * Key modifier. 
	 */
	unsigned int    modifier;
}MC_MOUSE_EVENT;


/**
 * \brief Key event structure.
 * \sa MC_MOUSE_EVENT, MC_CONTEXT_EVENT
 */
typedef struct _mc_key_evt {
	/**
	 * Key event type.
	 */
	MC_KEY_EVENT_TYPE   type;
	/**
	 * Key code value.
	 */
	MC_VIRTUAL_KEY 	     key;
	/**
	 * Key modifier. 
	 */
	unsigned int    modifier;
}MC_KEY_EVENT;

/**
 * \brief Context menu event structure.
 * \sa MC_KEY_EVENT, MC_MOUSE_EVENT
 */
typedef struct _mc_context_evt {
	/**
	 * Mouse event point.
	 */
	MC_POINT      	   point;
	/**
	 * Key modifier. 
	 */
	unsigned int    modifier;
}MC_CONTEXT_EVENT;
#endif

#if 0
/**
 * \fn MC_STATUS macross_mouse_event(MaCrossView* view, const MC_MOUSE_EVENT *event)
 * \brief Process a mouse event for web view.
 *
 * \param view     Pointer to an existing webview object.
 * \param event    Pointer to a mouse event.
 *
 * \return
 *         - MC_STATUS_SUCCESS on success.
 *         - Other status code on failed.
 *
 * \sa macross_keyboard_event, macross_context_menu_event
 */
MACROSS_API MC_STATUS macross_mouse_event(MaCrossView* view, const MC_MOUSE_EVENT *event);
/**
 * \fn MC_STATUS macross_keyboard_event(MaCrossView* view, const MC_KEY_EVENT *event)
 * \brief Process a key board event for web view.
 *
 * \param view     Pointer to an existing webview object.
 * \param event    Pointer to a key board event.
 *
 * \return
 *         - MC_STATUS_SUCCESS on success.
 *         - Other status code on failed.
 *
 * \sa macross_mouse_event, macross_context_menu_event
 */
MACROSS_API MC_STATUS macross_keyboard_event(MaCrossView* view, const MC_KEY_EVENT *event);
/**
 * \fn MC_STATUS macross_context_menu_event(MaCrossView* view, const MC_CONTEXT_EVENT *event)
 * \brief Process a context menu event for web view.
 *
 * \param view     Pointer to an existing webview object.
 * \param event    Pointer to a context menu event.
 *
 * \return
 *         - MC_STATUS_SUCCESS on success.
 *         - Other status code on failed.
 *
 * \sa macross_mouse_event, macross_keyboard_event
 */
MACROSS_API MC_STATUS macross_context_menu_event(MaCrossView* view, const MC_CONTEXT_EVENT *event);
#endif

#if 0
/**
 * \fn MC_STATUS macross_view_set_encoding(MaCrossView* view, MC_ENCODING_NAME encoding)
 * \brief Set the text encoding name for the webview.
 *
 * \param view  	Pointer to an existing webview object.
 * \param encoding  The encoding name. 
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_get_encoding
 */
MACROSS_API MC_STATUS macross_view_set_encoding(MaCrossView* view, MC_ENCODING_NAME encoding);

/**
 * \fn MC_STATUS macross_view_get_encoding(MaCrossView* view, MC_ENCODING_NAME* encoding)
 * \brief Get the text encoding name of the webview.
 *
 * \param view  	Pointer to an existing webview object.
 * \param encoding  Pointer to a buffer receiving the encoding name.
 *
 * \return
 * 		- MC_STATUS_SUCCESS on success.
 * 		- Other status code on failed.
 *
 * \sa macross_view_set_encoding
 */
MACROSS_API MC_STATUS macross_view_get_encoding(MaCrossView* view, MC_ENCODING_NAME* encoding);

#endif
