/*
 * FrameNetworkingContextDavinci.cpp: FrameNetworkingContextDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "FrameNetworkingContextDavinci.h"

#include "NotImplemented.h"
#include "ResourceError.h"

using namespace WebCore;

namespace WebKit {

FrameNetworkingContextDavinci::FrameNetworkingContextDavinci(Frame* frame, const String& userAgent)
    : FrameNetworkingContext(frame)
    , m_userAgent(userAgent)
{
}

String FrameNetworkingContextDavinci::userAgent() const
{
    return m_userAgent;
}

String FrameNetworkingContextDavinci::referrer() const
{
    return frame()->loader().referrer();
}

WebCore::ResourceError FrameNetworkingContextDavinci::blockedError(const WebCore::ResourceRequest&) const
{
    notImplemented();
    return WebCore::ResourceError();
}

} // namespace WebKit
