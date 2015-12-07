/*
 * RunLoopDavinci.cpp: RunLoop implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "RunLoop.h"

#include <wtf/OwnPtr.h>
#include <wtf/PassOwnPtr.h>

namespace WebCore {

RunLoop::RunLoop()
{
}

RunLoop::~RunLoop()
{
}

void RunLoop::run()
{
}

void RunLoop::stop()
{
}

void RunLoop::wakeUp()
{
}

RunLoop::TimerBase::TimerBase(RunLoop*)
{
}

RunLoop::TimerBase::~TimerBase()
{
    stop();
}

void RunLoop::TimerBase::start(double nextFireInterval, bool repeat)
{
}

void RunLoop::TimerBase::stop()
{
}

bool RunLoop::TimerBase::isActive() const
{
    return false;
}

} // namespace WebCore
