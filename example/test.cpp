#include <stdio.h>

#include <config.h>
#include <wtf/ExportMacros.h>
#include <wtf/MainThread.h>

#include "Frame.h"
#include "FrameView.h"
#include "InitializeThreading.h"
#include "PlatformStrategiesDavinci.h"

using namespace WebCore;

int main(int, char*[])
{
    JSC::initializeThreading();
    WTF::initializeMainThread();
    //PlatformStrategiesDavinci::initialize();



    return 0;
}
