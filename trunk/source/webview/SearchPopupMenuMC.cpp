/*
** SearchPopupMenu.cpp: SearchPopupMenu implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "SearchPopupMenu.h"
#include "PopupMenuClient.h"
#include "Debug.h"

namespace WebCore {

SearchPopupMenu::SearchPopupMenu(PopupMenuClient* client)
    :PopupMenu(client)
{
    notImplemented();
}

void SearchPopupMenu::saveRecentSearches(const AtomicString& name, const Vector<String>& searchItems)
{
    notImplemented();
}

void SearchPopupMenu::loadRecentSearches(const AtomicString& name, Vector<String>& searchItems)
{
    notImplemented();
}

bool SearchPopupMenu::enabled()
{
    notImplemented();
    return false;
}

}
