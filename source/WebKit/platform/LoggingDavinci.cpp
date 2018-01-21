/*
 * LoggingDavinci.cpp: Logging implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Logging.h"

#if !LOG_DISABLED

#include <wtf/text/WTFString.h>

namespace WebCore {

String logLevelString()
{
    char* logEnv = getenv("WEBKIT_DEBUG");
    if (!logEnv)
        return emptyString();

    // To disable logging notImplemented set the DISABLE_WARNING environment variable to 1.
    String logLevel = "NotYetImplemented,";
    logLevel.append(logEnv);
    return logLevel;
}

}

#endif // !LOG_DISABLED
