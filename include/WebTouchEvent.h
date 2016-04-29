/*
 * WebTouchEvent.h: TouchEvent define in davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_TOUCH_EVENT_H_
#define _DAVINCI_TOUCH_EVENT_H_

namespace davinci {

/**
 * \defgroup event InputEvent
 * @{
 */
/**
 * \defgroup eventclass EventObject
 * @{
 */
class WebTouchEventImpl;

class EXPORT_API WebTouchEvent : public WebEvent
{
public:
    WebTouchEvent();
    virtual ~WebTouchEvent();
private:
    WebTouchEventImpl* m_impl;
    DECLARE_NO_COPY_AND_ASSIGN(WebTouchEvent);
};

/** @} end of eventclass*/
/** @} end of event*/

} /* namespace davinci */

#endif /*_DAVINCI_TOUCH_EVENT_H_*/
