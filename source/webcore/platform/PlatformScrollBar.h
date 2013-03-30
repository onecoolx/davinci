#ifndef PlatformScrollbar_h
#define PlatformScrollbar_h

#include "Widget.h"
#include "ScrollBar.h"
#include "Timer.h"
#include "Color.h"


namespace WebCore {

enum ScrollbarPart { NoPart, BackButtonPart, BackTrackPart, ThumbPart, ForwardTrackPart, ForwardButtonPart };

class PlatformScrollbar : public Widget, public Scrollbar {
public:
    PlatformScrollbar(ScrollbarClient*, ScrollbarOrientation, ScrollbarControlSize);

    virtual ~PlatformScrollbar();

    virtual bool isWidget() const { return true; }

    virtual void setParent(ScrollView*);

    virtual int width() const;
    virtual int height() const;
    virtual void setRect(const IntRect&);
    virtual void setEnabled(bool);
    virtual void paint(GraphicsContext*, const IntRect& damageRect);

    virtual bool handleMouseMoveEvent(const PlatformMouseEvent&);
    virtual bool handleMouseOutEvent(const PlatformMouseEvent&);
    virtual bool handleMousePressEvent(const PlatformMouseEvent&);
    virtual bool handleMouseReleaseEvent(const PlatformMouseEvent&);

    virtual IntRect windowClipRect() const;

    static void themeChanged();
    static int horizontalScrollbarHeight(ScrollbarControlSize size = RegularScrollbar);
    static int verticalScrollbarWidth(ScrollbarControlSize size = RegularScrollbar);
    Color cornerColor (void);

    void autoscrollTimerFired(Timer<PlatformScrollbar>*);

protected:    
    virtual void updateThumbPosition();
    virtual void updateThumbProportion();

private:
    IntRect backButtonRect() const;
    IntRect forwardButtonRect() const;
    IntRect trackRect() const;
    IntRect thumbRect() const;
    IntRect gripperRect(const IntRect& thumbRect) const;    
    void splitTrack(const IntRect& trackRect, IntRect& beforeThumbRect, IntRect& thumbRect, IntRect& afterThumbRect) const;

    int thumbPosition() const;
    int thumbLength() const;
    int trackLength() const;

    void paintButton(GraphicsContext*, const IntRect& buttonRect, bool start, const IntRect& damageRect) const;
    void paintTrack(GraphicsContext*, const IntRect& trackRect, bool start, const IntRect& damageRect) const;
    void paintThumb(GraphicsContext*, const IntRect& thumbRect, const IntRect& damageRect) const;
    void paintGripper(GraphicsContext*, const IntRect& gripperRect) const;
    
    ScrollbarPart hitTest(const PlatformMouseEvent&);
    
    void startTimerIfNeeded(double delay);
    void stopTimerIfNeeded();
    void autoscrollPressedPart(double delay);
    ScrollDirection pressedPartScrollDirection();
    ScrollGranularity pressedPartScrollGranularity();

    bool thumbUnderMouse();

    void invalidatePart(ScrollbarPart);
    void invalidateTrack();

    ScrollbarPart m_hoveredPart;
    ScrollbarPart m_pressedPart;
    int m_pressedPos;
    Timer<PlatformScrollbar> m_scrollTimer;
    bool m_overlapsResizer;
    static Color g_cornerColor;
};

}

#endif // PlatformScrollbar_h

