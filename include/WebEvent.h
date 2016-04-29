/*
 * WebEvent.h: Event define in davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_EVENT_H_
#define _DAVINCI_EVENT_H_

namespace davinci {

/**
 * \defgroup event InputEvent
 * @{
 */

/**
 * \defgroup eventclass EventObject
 * @{
 */

class EXPORT_API WebEvent : public WebObject
{
public:
    virtual ~WebEvent() { }
};

/** @} end of eventclass*/
/** @} end of event*/

} /* namespace davinci */

#endif /*_DAVINCI_EVENT_H_*/
