/*
** InspectorClient.cpp: InspectorClient implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "InspectorClientPS.h"

#include "Debug.h"

namespace WebCore
{

InspectorClientPS::InspectorClientPS()
{
}

InspectorClientPS::~InspectorClientPS()
{
}

Page* InspectorClientPS::createPage()
{
    notImplemented();
    return NULL;
}

void InspectorClientPS::showWindow()
{
    notImplemented();
}

void InspectorClientPS::closeWindow()
{
    notImplemented();
}

void InspectorClientPS::attachWindow()
{
    notImplemented();
}

void InspectorClientPS::detachWindow()
{
    notImplemented();
}

void InspectorClientPS::highlight(Node*)
{
    notImplemented();
}

void InspectorClientPS::hideHighlight()
{
    notImplemented();
}

void InspectorClientPS::inspectedURLChanged(const String& newURL)
{
    notImplemented();
}

}

