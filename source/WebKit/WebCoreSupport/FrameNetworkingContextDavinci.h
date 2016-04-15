/*
 * FrameNetworkingContextDavinci.h: FrameNetworkingContextDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef FrameNetworkingContextDavinci_h
#define FrameNetworkingContextDavinci_h

#include "FrameNetworkingContext.h"

namespace WebKit {

class FrameNetworkingContextDavinci : public WebCore::FrameNetworkingContext {
public:
    static PassRefPtr<FrameNetworkingContextDavinci> create(WebCore::Frame* frame, const WTF::String& userAgent)
    {
        return adoptRef(new FrameNetworkingContextDavinci(frame, userAgent));
    }

    virtual WTF::String userAgent() const;
    virtual WTF::String referrer() const;
    virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest&) const;

private:
    FrameNetworkingContextDavinci(WebCore::Frame* frame, const WTF::String& userAgent);

    WTF::String m_userAgent;
};

} // namespace WebKit

#endif // FrameNetworkingContextDavinci_h
