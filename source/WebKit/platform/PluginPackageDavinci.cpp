/*
 * PluginPackageDavinci.cpp: PluginPackage implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PluginPackage.h"

#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "PluginDatabase.h"
#include "PluginDebug.h"
#include "npruntime_impl.h"

#include <wtf/text/CString.h>

namespace WebCore {

bool PluginPackage::fetchInfo()
{
    return false;
}

uint16_t PluginPackage::NPVersion() const
{
    return NPVERS_HAS_PLUGIN_THREAD_ASYNC_CALL;
}

bool PluginPackage::load()
{
    return false;
}

}
