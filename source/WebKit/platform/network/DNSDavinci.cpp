/*
 * DNSDavinci.cpp: DNS implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "DNS.h"

#include "DNSResolveQueue.h"
#include "NotImplemented.h"
#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

bool DNSResolveQueue::platformProxyIsEnabledInSystemPreferences()
{
    notImplemented();
    return false;
}

void DNSResolveQueue::platformResolve(const String&)
{
    notImplemented();
}

void prefetchDNS(const String& host)
{
    notImplemented();
}

}

