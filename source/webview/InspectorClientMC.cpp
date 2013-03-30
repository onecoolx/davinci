/*
** InspectorClient.cpp: InspectorClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "InspectorClientMC.h"

#include "Debug.h"

namespace WebCore
{

InspectorClientMC::InspectorClientMC()
{
}

InspectorClientMC::~InspectorClientMC()
{
}

Page* InspectorClientMC::createPage()
{
    notImplemented();
    return NULL;
}

void InspectorClientMC::showWindow()
{
    notImplemented();
}

void InspectorClientMC::closeWindow()
{
    notImplemented();
}

void InspectorClientMC::attachWindow()
{
    notImplemented();
}

void InspectorClientMC::detachWindow()
{
    notImplemented();
}

void InspectorClientMC::highlight(Node*)
{
    notImplemented();
}

void InspectorClientMC::hideHighlight()
{
    notImplemented();
}

void InspectorClientMC::inspectedURLChanged(const String& newURL)
{
    notImplemented();
}

}

