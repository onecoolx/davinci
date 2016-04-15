/*
 * InspectorClientDavinci.cpp: InspectorClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "InspectorClientDavinci.h"

#include "NotImplemented.h"

using namespace WebCore;

namespace WebKit {

InspectorClientDavinci::InspectorClientDavinci(WebView* webView)
    : m_inspectedWebView(webView)
{
}

InspectorClientDavinci::~InspectorClientDavinci()
{
}

void InspectorClientDavinci::inspectorDestroyed()
{
    delete this;
}

InspectorFrontendChannel* InspectorClientDavinci::openInspectorFrontend(InspectorController* controller)
{
    notImplemented();
    return 0;
}

void InspectorClientDavinci::closeInspectorFrontend()
{
    notImplemented();
}

void InspectorClientDavinci::bringFrontendToFront()
{
    notImplemented();
}

void InspectorClientDavinci::releaseFrontendPage()
{
    notImplemented();
}

void InspectorClientDavinci::highlight()
{
    notImplemented();
}

void InspectorClientDavinci::hideHighlight()
{
    notImplemented();
}

void InspectorClientDavinci::populateSetting(const String& key, String* value)
{
    notImplemented();
}

void InspectorClientDavinci::storeSetting(const String& key, const String& value)
{
    notImplemented();
}

bool InspectorClientDavinci::sendMessageToFrontend(const String& message)
{
    notImplemented();
    return false;
}

} // namespace WebKit
