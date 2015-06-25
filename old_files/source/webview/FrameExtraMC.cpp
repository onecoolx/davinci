
#include "config.h"
#include "Frame.h"
#include "Debug.h"

#if USE(NPOBJECT)
#include "PluginViewPS.h"
using namespace KJS::Bindings;
#endif //USE(NPOBJECT)

namespace WebCore {

#if USE(NPOBJECT)
KJS::Bindings::Instance* Frame::createScriptInstanceForWidget(Widget* widget)
{
#if ENABLE(PLUGIN)
    PluginViewPS *pluginView = (PluginViewPS*)widget;
    if (pluginView)
       return pluginView->bindingInstance(); 
#endif
    return 0;
}

void Frame::clearPlatformScriptObjects()
{
    notImplemented();
}
#endif //USE(NPOBJECT)

DragImageRef Frame::dragImageForSelection()
{    
    notImplemented();
    return 0;
}

void Frame::dashboardRegionsChanged()
{
    notImplemented();
}

void Frame::setNeedsReapplyStyles() 
{
     notImplemented();
}

void Frame::issueTransposeCommand() 
{
     notImplemented();
}

}
