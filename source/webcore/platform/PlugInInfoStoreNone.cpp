#include "config.h"
#include "PlugInInfoStore.h"

namespace WebCore {

PluginInfo* PlugInInfoStore::createPluginInfoForPluginAtIndex(unsigned i) 
{ 
    return 0;
}

unsigned PlugInInfoStore::pluginCount() const
{
    return 0;
}

bool PlugInInfoStore::supportsMIMEType(const String& mimeType) 
{
    return false;
}

void refreshPlugins(bool reloadOpenPages)
{
}

}

