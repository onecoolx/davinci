/*
** SharedTimer.cpp: SharedTimer implements by libev.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"

#include "SharedTimer.h"
#include "SystemTime.h"
#include <wtf/MathExtras.h>

namespace WebCore {
static double timeout = 0;
static bool timer_enable = false;
static void (*sharedTimerFiredFunction)() = 0;

void setSharedTimerFiredFunction(void (*f)())
{
    sharedTimerFiredFunction = f;
}

static void timerFired(void)
{
    if (sharedTimerFiredFunction)
        sharedTimerFiredFunction();
}

void setSharedTimerFireTime(double fireTime)
{
	double current = currentTime();
    double interval = fireTime - current;
    if (interval < 0) 
		interval = 0;

    stopSharedTimer();
	timeout = interval+current;
	timer_enable = true;
}

void stopSharedTimer()
{
    if (timer_enable)
		timer_enable = false;
}

void eventInitialize(void)
{
}

void eventShatdown(void)
{
}

void eventDispatch(void)
{
	if (timer_enable && ((currentTime() - timeout) > 0)) {
    	stopSharedTimer();
		timerFired();
	}

}

}
