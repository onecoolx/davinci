/*
** ChromeClient.h: ChromeClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef ChromeClientMC_H
#define ChromeClientMC_H

#include "ChromeClient.h"
#include "FloatRect.h"
#include "WindowFeatures.h"
#include "Element.h"

#include "macross.h"

namespace WebCore {

class ChromeClientMC : public ChromeClient
{
public:
    ChromeClientMC(_mc_view*, int, int);
    virtual ~ChromeClientMC();

    virtual void chromeDestroyed(){delete this;}

    virtual void setWindowRect(const FloatRect&);
    virtual FloatRect windowRect();

    virtual float scaleFactor();

    virtual void focus();
    virtual void unfocus();

    virtual bool canTakeFocus(FocusDirection);
    virtual void takeFocus(FocusDirection);

    virtual void setWindowFeature(const WindowFeatures&);
    virtual Page* createWindow(Frame*, const FrameLoadRequest&, const WindowFeatures&);

    virtual bool canRunModal();
    virtual void runModal();

    virtual bool toolbarVisible();
    virtual bool menubarVisible();
    virtual bool scrollbarsVisible();
    virtual bool statusbarVisible();
    virtual bool locationbarVisible();
    virtual bool personalbarVisible();

    virtual void addMessageToConsole(const String& message, unsigned int lineNumber, const String& sourceID);

    virtual bool canRunBeforeUnloadConfirmPanel();
    virtual bool runBeforeUnloadConfirmPanel(const String& message, Frame* frame);

    virtual void closeWindowSoon();

    virtual void runJavaScriptAlert(Frame*, const String&);
    virtual bool runJavaScriptConfirm(Frame*, const String&);
    virtual bool runJavaScriptPrompt(Frame*, const String& message, const String& defaultValue, String& result);

    virtual void setStatusbarText(const String&);
    virtual bool shouldInterruptJavaScript();
    virtual bool tabsToLinks() const;

    virtual IntRect windowResizerRect() const;
    virtual void addToDirtyRegion(const IntRect&);
    virtual void scrollBackingStore(int dx, int dy, const IntRect& scrollViewRect, const IntRect& clipRect);
    virtual void updateBackingStore();

    virtual void mouseDidMoveOverElement(const HitTestResult&, unsigned modifierFlags);

    virtual void setToolTip(const String&, const IntPoint&);
    virtual void print(Frame*);

    void setFocused(bool b) { m_focused = b; }
    bool isFocused(void) const { return m_focused; }

	void focusChangedRect(const IntRect&);

private:
    _mc_view* m_view;
    WindowFeatures m_features;
    Element* m_lastHoverElement;
    unsigned m_lastTooltipId;
    bool m_focused;
};

}

#endif // ChromeClientMg_H
