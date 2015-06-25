/*
 * Copyright (C) 2006 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef POPUPMENU_H
#define POPUPMENU_H

#include "Shared.h"
#include "IntRect.h"
#include "PopupMenuClient.h"
#include <wtf/PassRefPtr.h>

#include "ScrollBar.h"
#include <wtf/RefPtr.h>
#include "macross.h"
#include "WidgetView.h"

namespace WebCore {

class FrameView;
class PlatformScrollbar;

class PopupMenu : public Shared<PopupMenu>, public WidgetView
                , private ScrollbarClient
{
public:
    static PassRefPtr<PopupMenu> create(PopupMenuClient* client) { return new PopupMenu(client); }
    ~PopupMenu();
    
    void disconnectClient() { m_popupClient = 0; }

    void show(const IntRect&, FrameView*, int index);
    void hide();

    void updateFromElement();
	void updateRect(int x, int y, int width, int height);
	void scrollRect(int sx, int sy, int x, int y, int width, int height);
    
    PopupMenuClient* client() const { return m_popupClient; }

    static bool itemWritingDirectionIsNatural();

    PlatformScrollbar* scrollBar() const { return m_scrollBar.get(); }

    bool up(unsigned lines = 1);
    bool down(unsigned lines = 1);

    int itemHeight() const { return m_itemHeight; }
    const IntRect& windowRect() const { return m_windowRect; }
    IntRect clientRect() const;

    int visibleItems() const;

    int listIndexAtPoint(const IntPoint&) const;

    bool setFocusedIndex(int index, bool hotTracking = false);
    int focusedIndex() const;
    void focusFirst();
    void focusLast();

    void paint(const IntRect& damageRect, GraphicsContext*);

    _mc_popup_menu* popupHandle() const { return m_popup; }

    void setWasClicked(bool b = true) { m_wasClicked = b; }
    bool wasClicked() const { return m_wasClicked; }

    void setScrollOffset(int offset) { m_scrollOffset = offset; }
    int scrollOffset() const { return m_scrollOffset; }

    bool scrollToRevealSelection();

    void incrementWheelDelta(int delta);
    void reduceWheelDelta(int delta);
    int wheelDelta() const { return m_wheelDelta; }

    bool scrollbarCapturingMouse() const { return m_scrollbarCapturingMouse; }
    void setScrollbarCapturingMouse(bool b) { m_scrollbarCapturingMouse = b; }
    virtual IntRect windowClientRect() const;
protected:
    PopupMenu(PopupMenuClient* client);

    virtual IntRect windowClipRect() const;
    virtual void valueChanged(Scrollbar*);
private:
    PopupMenuClient* m_popupClient;

    void calculatePositionAndSize(const IntRect&, FrameView*);
    void invalidateItem(int index);

    RefPtr<PlatformScrollbar> m_scrollBar;
    _mc_popup_menu* m_popup;
	_mc_view *m_view;
    bool m_wasClicked;
    IntRect m_windowRect;
    int m_itemHeight;
    int m_scrollOffset;
    int m_wheelDelta;
    int m_focusedIndex;
    bool m_scrollbarCapturingMouse;
};

}

#endif
