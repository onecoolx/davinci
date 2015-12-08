/*
 * LanguageDavinci.cpp: Language implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Language.h"

#include <locale.h>
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

static String platformLanguage()
{
    char* localeDefault = setlocale(LC_CTYPE, 0);

    if (!localeDefault)
        return String("c");

    String locale = String(localeDefault);
    locale.replace('_', '-');
    size_t position = locale.find('.');
    if (position != notFound)
        locale = locale.left(position);

    return locale;
}

Vector<String> platformUserPreferredLanguages()
{
    Vector<String> userPreferredLanguages;
    userPreferredLanguages.append(platformLanguage());
    return userPreferredLanguages;
}

}
