/*
 * ContextMenuDavinci.cpp: ContextMenu implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#if ENABLE(CONTEXT_MENUS)

#include "ContextMenu.h"

namespace WebCore {

ContextMenu::ContextMenu()
{
}

ContextMenu::ContextMenu(const PlatformMenuDescription menu)
    : m_platformDescription(menu)
{
}

ContextMenu::~ContextMenu()
{
}

void ContextMenu::appendItem(ContextMenuItem& item)
{
}

void ContextMenu::setPlatformDescription(PlatformMenuDescription menu)
{
}

PlatformMenuDescription ContextMenu::platformDescription() const
{
    return m_platformDescription;
}

PlatformMenuDescription ContextMenu::releasePlatformDescription()
{
    PlatformMenuDescription description = m_platformDescription;
    m_platformDescription = 0;

    return description;
}

unsigned ContextMenu::itemCount() const
{
}

Vector<ContextMenuItem> contextMenuItemVector(const PlatformMenuDescription menu)
{
}

PlatformMenuDescription platformMenuDescription(Vector<ContextMenuItem>& subMenuItems)
{
}

}

#endif // ENABLE(CONTEXT_MENUS)
