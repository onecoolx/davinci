/*
 * RenderThemeDavinci.h: RenderTheme implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef RenderThemeDavinci_h
#define RenderThemeDavinci_h

#include "RenderTheme.h"

namespace WebCore {

class RenderThemeDavinci : public RenderTheme {
public:
    static PassRefPtr<RenderTheme> create();

    virtual ~RenderThemeDavinci();

    virtual String extraDefaultStyleSheet() OVERRIDE;
    virtual String extraQuirksStyleSheet() OVERRIDE;
    virtual String extraPlugInsStyleSheet() OVERRIDE;

    virtual void systemFont(WebCore::CSSValueID, FontDescription&) const OVERRIDE;

#if ENABLE(PROGRESS_ELEMENT)
    // Returns the repeat interval of the animation for the progress bar.
    virtual double animationRepeatIntervalForProgressBar(RenderProgress*) const OVERRIDE;
    // Returns the duration of the animation for the progress bar.
    virtual double animationDurationForProgressBar(RenderProgress*) const OVERRIDE;
#endif

#if ENABLE(METER_ELEMENT)
    virtual IntSize meterSizeForBounds(const RenderMeter*, const IntRect&) const OVERRIDE;
    virtual bool supportsMeter(ControlPart) const OVERRIDE;
#endif

protected:
    // The platform selection color.
    virtual Color platformActiveSelectionBackgroundColor() const OVERRIDE;
    virtual Color platformInactiveSelectionBackgroundColor() const OVERRIDE;
    virtual Color platformActiveSelectionForegroundColor() const OVERRIDE;
    virtual Color platformInactiveSelectionForegroundColor() const OVERRIDE;

    virtual Color platformActiveListBoxSelectionBackgroundColor() const OVERRIDE;
    virtual Color platformInactiveListBoxSelectionBackgroundColor() const OVERRIDE;
    virtual Color platformActiveListBoxSelectionForegroundColor() const OVERRIDE;
    virtual Color platformInactiveListBoxSelectionForegroundColor() const OVERRIDE;

    // Highlighting colors for TextMatches.
    virtual Color platformActiveTextSearchHighlightColor() const OVERRIDE;
    virtual Color platformInactiveTextSearchHighlightColor() const OVERRIDE;

    virtual Color platformFocusRingColor() const OVERRIDE;

#if ENABLE(TOUCH_EVENTS)
    virtual Color platformTapHighlightColor() const OVERRIDE;
#endif

    virtual bool paintButton(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual bool paintTextField(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual bool paintTextArea(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;

    virtual bool paintCheckbox(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual void setCheckboxSize(RenderStyle*) const OVERRIDE;

    virtual bool paintRadio(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual void setRadioSize(RenderStyle*) const OVERRIDE;

    virtual bool paintMenuList(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual void adjustMenuListStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;
    virtual bool paintMenuListButton(RenderObject* o, const PaintInfo& i, const IntRect& r) OVERRIDE { return paintMenuList(o, i, r); }

    virtual void adjustInnerSpinButtonStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;
    virtual bool paintInnerSpinButton(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;

#if ENABLE(PROGRESS_ELEMENT)
    virtual void adjustProgressBarStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;
    virtual bool paintProgressBar(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
#endif

#if ENABLE(METER_ELEMENT)
    virtual void adjustMeterStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;
    virtual bool paintMeter(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
#endif

    virtual bool paintSliderTrack(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual void adjustSliderTrackStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;

    virtual bool paintSliderThumb(RenderObject*, const PaintInfo&, const IntRect&) OVERRIDE;
    virtual void adjustSliderThumbStyle(StyleResolver*, RenderStyle*, Element*) const OVERRIDE;

    virtual void adjustSliderThumbSize(RenderStyle*, Element*) const OVERRIDE;

#if ENABLE(DATALIST_ELEMENT)
    virtual IntSize sliderTickSize() const OVERRIDE;
    virtual int sliderTickOffsetFromTrackCenter() const OVERRIDE;
    virtual LayoutUnit sliderTickSnappingThreshold() const OVERRIDE;

    virtual bool supportsDataListUI(const AtomicString&) const OVERRIDE;
#endif

private:
    RenderThemeDavinci();
};

}

#endif // RenderThemeDavinci_h
