/*
 * PluginDatabaseDavinci.cpp: PluginDatabase implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PluginDatabase.h"

#include "NotImplemented.h"

namespace WebCore {

Vector<String> PluginDatabase::defaultPluginDirectories()
{
    notImplemented();
    return Vector<String>();
}

void PluginDatabase::getPluginPathsInDirectories(HashSet<String>& paths) const
{
    notImplemented();
}

bool PluginDatabase::isPreferredPluginDirectory(const String& directory)
{
    notImplemented();
    return false;
}

} // namespace WebCore
