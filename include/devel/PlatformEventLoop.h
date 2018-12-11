/*
 * PlatformEventLoop.h: Platform interface for event loop.
 *
 * Copyright(C) 2018 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_PLATFORM_EVENTLOOP_H_
#define _DAVINCI_PLATFORM_EVENTLOOP_H_

namespace davinci {
namespace platform {
/**
 * \defgroup devel Platform
 * @{
 */

class PlatformEventLoop
{
public:
    virtual ~PlatformEventLoop() { }
};


bool EXPORT_API SetupEventLoop(PlatformEventLoop* loop);

/** @} end of devel*/
} /* namespace platform*/
} /* namespace davinci */

#endif /*_DAVINCI_PLATFORM_EVENTLOOP_H_*/
