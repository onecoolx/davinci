
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

