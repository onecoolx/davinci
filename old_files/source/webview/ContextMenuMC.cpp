/*
** ContextMenuMC.cpp: ContextMenu implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "ContextMenu.h"
#include "Debug.h"

namespace WebCore {

ContextMenu::ContextMenu(const HitTestResult & result)
    :m_hitTestResult(result)
{
}

ContextMenu::~ContextMenu()
{
}

}
