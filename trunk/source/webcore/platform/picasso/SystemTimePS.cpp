/*
** SystemTimePS.cpp: SystemTime implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#if HAVE(SYS_TIME_H)
#include <sys/time.h>
#endif
#include "DateMath.h"
#include "SystemTime.h"

#if !HAVE(GETTIMEOFDAY) && COMPILER(GCC)
static struct timespec ts;
void inline gettimeofday(struct timeval *tv, struct timezone *tz)
{
    clock_gettime(CLOCK_REALTIME,&ts);
    tv->tv_sec=ts.tv_sec;
    tv->tv_usec=ts.tv_nsec/1000;
}
#endif

namespace WebCore {

#if COMPILER(MSVC)
double currentTime()
{
    return KJS::getCurrentUTCTime() * 0.001;
}
#else
double currentTime()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (double)tv.tv_sec + (double)(tv.tv_usec / 1000000.0);
}
#endif

}
