
#include "config.h"
#include <wtf/StringExtras.h>
#include "WebGlobal.h"
#include "SchemeExtension.h"

namespace WebCore {


bool isSupportedInternalScheme(const char *scheme)
{
    if (!scheme)
        return false;

	static const char *builtinSchemes[] = {"http", "ftp", "https", "ftps", "file", "data"};
    for (size_t i=0; i<TABLE_SIZE(builtinSchemes); i++) {
        if (!strcasecmp(builtinSchemes[i], scheme))
            return true;
    }
    return false;
}

#if ENABLE(SCHEMEEXTENSION)

static Vector<SchemeHandler> *schemeHandler(void)
{
    static Vector<SchemeHandler> *handler = new Vector<SchemeHandler>;
    return handler;
}

static bool handleExtensionScheme(const KURL &url)
{
    Vector<SchemeHandler> *schemes= schemeHandler();
    if (!schemes)
        return false;

    size_t size = schemes->size();
    for (size_t i=0; i<size; i++) {
        SchemeHandler *handler = &schemes->at(i); 
        if (equalIgnoringCase(handler->scheme, url.protocol())) {
            (void)(*handler->cb)(url.url().latin1(), handler->param);
            return true;
        }
    }
    return false;
}

bool scheduleScheme(const KURL &url)
{
    if (isSupportedInternalScheme(url.protocol().latin1()))
        return false;

    if (handleExtensionScheme(url))
        return true;

    return false;
}

static bool validScheme(const char *scheme, int &size)
{
    const char *colon = strchr(scheme, ':');
    if (colon)
        size = (int)colon - (int)scheme;
    
    if (!isSchemeFirstChar(scheme[0]))
        return false;

    for (int i=1; i<size; i++) {
        if (! isSchemeChar(scheme[i]))
            return false;
    }
    return true;
}

bool RegisterSchemeHandler(const char *scheme, cb_scheme_callback cb, void *param)
{
    if (! scheme || !cb)
        return false;

    if (isSupportedInternalScheme(scheme))
        return false;

    Vector<SchemeHandler> *handler = schemeHandler();
    if (! handler)
        return false;

    int csize = strlen(scheme);
    if (! validScheme(scheme, csize))
        return false;

    String strScheme(scheme, csize);
    size_t size = handler->size();
    for (size_t i=0; i<size; i++) {
        if (equalIgnoringCase(handler->at(i).scheme, strScheme)) {
            handler->at(i).cb = cb;
            handler->at(i).param = param;
            return true;
        }
    }

    handler->resize(size+1);
    handler->at(size).scheme = strScheme;
    handler->at(size).cb = cb;
    handler->at(size).param = param;
    return true;
}

bool UnregisterSchemeHandler(const char *scheme)
{
    if (! scheme)
        return false;

    Vector<SchemeHandler> *handler = schemeHandler();
    if (!handler)
        return false;

    int csize = strlen(scheme);
    if (!validScheme(scheme, csize))
        return false;

    String strScheme(scheme, csize);
    size_t size = handler->size();
    for (size_t i=0; i<size; i++) {
        if (equalIgnoringCase(handler->at(i).scheme, strScheme)) {
            handler->remove(i);
            return true;
        }
    }
    return false;
}

#endif /* ENABLE(SCHEMEEXTENSION) */

} /* namespace WebCore */

