/*
 * SharedTimerDavinci.cpp: SharedTimer implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "SharedTimer.h"

#include <wtf/Assertions.h>
#include <wtf/CurrentTime.h>
#include <wtf/MainThread.h>

namespace WebCore {

void setSharedTimerFiredFunction(void (*func)())
{
}

void stopSharedTimer()
{
}

void setSharedTimerFireInterval(double interval)
{
}

}

