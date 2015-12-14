/*
 * ContextMenuItemDavinci.cpp: ContextMenuItem implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#if ENABLE(CONTEXT_MENUS)

#include "ContextMenuItem.h"

#include "ContextMenu.h"
#include <wtf/text/CString.h>

namespace WebCore {

ContextMenuItem::ContextMenuItem(PlatformMenuItemDescription item)
    : m_platformDescription(item)
{
}

ContextMenuItem::ContextMenuItem(ContextMenu* subMenu)
{
}

ContextMenuItem::ContextMenuItem(ContextMenuItemType type, ContextMenuAction action, const String& title, ContextMenu* subMenu)
{

}

ContextMenuItem::ContextMenuItem(ContextMenuItemType type, ContextMenuAction action, const String& title, bool enabled, bool checked)
{

}

ContextMenuItem::ContextMenuItem(ContextMenuAction action, const String& title, bool enabled, bool checked, Vector<ContextMenuItem>& subMenuItems)
{

}

ContextMenuItem::~ContextMenuItem()
{
}

PlatformMenuItemDescription ContextMenuItem::releasePlatformDescription()
{
    PlatformMenuItemDescription platformDescription = m_platformDescription;
    m_platformDescription = 0;
    return platformDescription;
}

ContextMenuItemType ContextMenuItem::type() const
{
    return ActionType;
}

void ContextMenuItem::setType(ContextMenuItemType type)
{
}

ContextMenuAction ContextMenuItem::action() const
{
	return ContextMenuItemTagNoAction;
}

void ContextMenuItem::setAction(ContextMenuAction action)
{
}

String ContextMenuItem::title() const
{
}

void ContextMenuItem::setTitle(const String& title)
{
}

PlatformMenuDescription ContextMenuItem::platformSubMenu() const
{
}

void ContextMenuItem::setSubMenu(ContextMenu* menu)
{
}

void ContextMenuItem::setSubMenu(Vector<ContextMenuItem>& subMenuItems)
{
    ContextMenu menu(platformMenuDescription(subMenuItems));
    setSubMenu(&menu);
}

void ContextMenuItem::setChecked(bool shouldCheck)
{
}

bool ContextMenuItem::checked() const
{
    return false;
}

bool ContextMenuItem::enabled() const
{
}

void ContextMenuItem::setEnabled(bool shouldEnable)
{
}

}

#endif // ENABLE(CONTEXT_MENUS)
