
#ifndef SchemeExtension_h
#define SchemeExtension_h

#include "config.h"
#include "macross.h"
#include "KURL.h"
#include "PlatformString.h" 
#include <wtf/Vector.h>

namespace WebCore {

#if ENABLE(SCHEMEEXTENSION)
struct SchemeHandler {
    String scheme;
    cb_scheme_callback cb;
    void *param;
};

bool RegisterSchemeHandler(const char *scheme, cb_scheme_callback cb, void *param);
bool UnregisterSchemeHandler(const char *scheme);
bool scheduleScheme(const KURL &url);
#endif /* ENABLE(SCHEMEEXTENSION) */

bool isSupportedInternalScheme(const char *scheme);

} /* namespace WebCore */

#endif /* SchemeExtension_h */
