/*
 * RenderThemeDavinci.cpp: RenderTheme implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "RenderThemeDavinci.h"

#include "InputTypeNames.h"
#include "PaintInfo.h"
#if ENABLE(PROGRESS_ELEMENT)
#include "RenderProgress.h"
#endif
#if ENABLE(METER_ELEMENT)
#include "HTMLMeterElement.h"
#include "RenderMeter.h"
#endif

namespace WebCore {

PassRefPtr<RenderTheme> RenderTheme::themeForPage(Page*)
{
    return RenderThemeDavinci::create();
}

PassRefPtr<RenderTheme> RenderThemeDavinci::create()
{
    return adoptRef(new RenderThemeDavinci);
}

RenderThemeDavinci::RenderThemeDavinci()
    : RenderTheme()
{
}

RenderThemeDavinci::~RenderThemeDavinci()
{

}

String RenderThemeDavinci::extraDefaultStyleSheet()
{
#if 0
    return themeEngine()->extraDefaultStyleSheet();
#else
	return String();
#endif
}

String RenderThemeDavinci::extraQuirksStyleSheet()
{
#if 0
    return themeEngine()->extraQuirksStyleSheet();
#else
	return String();
#endif
}

String RenderThemeDavinci::extraPlugInsStyleSheet()
{
#if 0
    return themeEngine()->extraPlugInsStyleSheet();
#else
	return String();
#endif
}

Color RenderThemeDavinci::platformActiveSelectionBackgroundColor() const
{
#if 0
    return toColor(themeEngine()->activeSelectionBackgroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformInactiveSelectionBackgroundColor() const
{
#if 0
    return toColor(themeEngine()->inactiveSelectionBackgroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformActiveSelectionForegroundColor() const
{
#if 0
    return toColor(themeEngine()->activeSelectionForegroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformInactiveSelectionForegroundColor() const
{
#if 0
    return toColor(themeEngine()->inactiveSelectionForegroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformActiveListBoxSelectionBackgroundColor() const
{
#if 0
    return toColor(themeEngine()->activeListBoxSelectionBackgroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformInactiveListBoxSelectionBackgroundColor() const
{
#if 0
    return toColor(themeEngine()->inactiveListBoxSelectionBackgroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformActiveListBoxSelectionForegroundColor() const
{
#if 0
    return toColor(themeEngine()->activeListBoxSelectionForegroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformInactiveListBoxSelectionForegroundColor() const
{
#if 0
    return toColor(themeEngine()->inactiveListBoxSelectionForegroundColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformActiveTextSearchHighlightColor() const
{
#if 0
    return toColor(themeEngine()->activeTextSearchHighlightColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformInactiveTextSearchHighlightColor() const
{
#if 0
    return toColor(themeEngine()->inactiveTextSearchHighlightColor());
#else
	return Color();
#endif
}

Color RenderThemeDavinci::platformFocusRingColor() const
{
#if 0
    return toColor(themeEngine()->focusRingColor());
#else
	return Color();
#endif
}

#if ENABLE(TOUCH_EVENTS)
Color RenderThemeDavinci::platformTapHighlightColor() const
{
#if 0
    return toColor(themeEngine()->tapHighlightColor());
#endif
}
#endif

void RenderThemeDavinci::systemFont(WebCore::CSSValueID, FontDescription&) const
{
}

bool RenderThemeDavinci::paintButton(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
#if 0
    WebKit::WebThemeEngine::ButtonExtraParams extraParams;
    extraParams.isDefault = isDefault(o);
    extraParams.hasBorder = true;
    extraParams.backgroundColor = defaultButtonBackgroundColor;
    if (o->hasBackground())
        extraParams.backgroundColor = o->style()->visitedDependentColor(CSSPropertyBackgroundColor).rgb();

    themeEngine()->paintButton(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect), extraParams);
#endif
    return false;
}

bool RenderThemeDavinci::paintTextField(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    // WebThemeEngine does not handle border rounded corner and background image
    // so return true to draw CSS border and background.
    if (o->style()->hasBorderRadius() || o->style()->hasBackgroundImage())
        return true;

#if 0
    themeEngine()->paintTextField(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect));
#endif
    return false;
}

bool RenderThemeDavinci::paintTextArea(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    return paintTextField(o, i, rect);
}

bool RenderThemeDavinci::paintCheckbox(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
#if 0
    WebKit::WebThemeEngine::ButtonExtraParams extraParams;
    extraParams.checked = isChecked(o);
    extraParams.indeterminate = isIndeterminate(o);

    themeEngine()->paintCheckbox(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect), extraParams);
#endif
    return false;
}

void RenderThemeDavinci::setCheckboxSize(RenderStyle* style) const
{
    // If the width and height are both specified, then we have nothing to do.
    if (!style->width().isIntrinsicOrAuto() && !style->height().isAuto())
        return;
#if 0
    IntSize size = themeEngine()->getCheckboxSize();
    setSizeIfAuto(style, size);
#endif
}

bool RenderThemeDavinci::paintRadio(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
#if 0
    WebKit::WebThemeEngine::ButtonExtraParams extraParams;
    extraParams.checked = isChecked(o);
    extraParams.indeterminate = isIndeterminate(o);

    themeEngine()->paintRadio(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect), extraParams);
#endif
    return false;
}

void RenderThemeDavinci::setRadioSize(RenderStyle* style) const
{
    // If the width and height are both specified, then we have nothing to do.
    if (!style->width().isIntrinsicOrAuto() && !style->height().isAuto())
        return;
#if 0
    IntSize size = themeEngine()->getRadioSize();
    setSizeIfAuto(style, size);
#endif
}

bool RenderThemeDavinci::paintMenuList(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
#if 0
    themeEngine()->paintMenuList(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect));
#endif
    return false;
}

void RenderThemeDavinci::adjustMenuListStyle(StyleResolver*, RenderStyle* style, Element*) const
{
    style->resetBorder();
    style->setWhiteSpace(PRE);

    int paddingTop = 0;
    int paddingLeft = 0;
    int paddingBottom = 0;
    int paddingRight = 0;
#if 0
    themeEngine()->getMenuListPadding(paddingTop, paddingLeft, paddingBottom, paddingRight);
#endif
    style->setPaddingTop(Length(paddingTop, Fixed));
    style->setPaddingRight(Length(paddingRight, Fixed));
    style->setPaddingBottom(Length(paddingBottom, Fixed));
    style->setPaddingLeft(Length(paddingLeft, Fixed));
}

#if ENABLE(PROGRESS_ELEMENT)
void RenderThemeDavinci::adjustProgressBarStyle(StyleResolver*, RenderStyle* style, Element*) const
{
    style->setBoxShadow(nullptr);
}

bool RenderThemeDavinci::paintProgressBar(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    RenderProgress* renderProgress = toRenderProgress(o);
#if 0
    WebKit::WebThemeEngine::ProgressBarExtraParams extraParams;
    extraParams.isDeterminate = renderProgress->isDeterminate();
    extraParams.position = renderProgress->position();
    extraParams.animationProgress = renderProgress->animationProgress();
    extraParams.animationStartTime = renderProgress->animationStartTime();
    themeEngine()->paintProgressBar(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect), extraParams);
#endif

    return false;
}

double RenderThemeDavinci::animationRepeatIntervalForProgressBar(RenderProgress*) const
{
#if 0
    return themeEngine()->getAnimationRepeatIntervalForProgressBar();
#else
	return 0;
#endif
}

double RenderThemeDavinci::animationDurationForProgressBar(RenderProgress*) const
{
#if 0
    return themeEngine()->getAnimationDurationForProgressBar();
#else
	return 0;
#endif
}
#endif

bool RenderThemeDavinci::paintSliderTrack(RenderObject* object, const PaintInfo& info, const IntRect& rect)
{
#if 0
    themeEngine()->paintSliderTrack(webCanvas(info), getWebThemeState(this, object), rect);
#endif
#if ENABLE(DATALIST_ELEMENT)
    paintSliderTicks(object, info, rect);
#endif
    return false;
}

void RenderThemeDavinci::adjustSliderTrackStyle(StyleResolver*, RenderStyle* style, Element*) const
{
    style->setBoxShadow(nullptr);
}

bool RenderThemeDavinci::paintSliderThumb(RenderObject* object, const PaintInfo& info, const IntRect& rect)
{
#if 0
    themeEngine()->paintSliderThumb(webCanvas(info), getWebThemeState(this, object), rect);
#endif

    return false;
}

void RenderThemeDavinci::adjustSliderThumbStyle(StyleResolver* styleResolver, RenderStyle* style, Element* element) const
{
    RenderTheme::adjustSliderThumbStyle(styleResolver, style, element);
    style->setBoxShadow(nullptr);
}

const int SliderThumbWidth = 10;
const int SliderThumbHeight = 20;

void RenderThemeDavinci::adjustSliderThumbSize(RenderStyle* style, Element*) const
{
    ControlPart part = style->appearance();
    if (part == SliderThumbVerticalPart) {
        style->setWidth(Length(SliderThumbWidth, Fixed));
        style->setHeight(Length(SliderThumbHeight, Fixed));
    } else if (part == SliderThumbHorizontalPart) {
        style->setWidth(Length(SliderThumbWidth, Fixed));
        style->setHeight(Length(SliderThumbHeight, Fixed));
    }
}

#if ENABLE(DATALIST_ELEMENT)
IntSize RenderThemeDavinci::sliderTickSize() const
{
    return IntSize(1, 6);
}

int RenderThemeDavinci::sliderTickOffsetFromTrackCenter() const
{
    return -12;
}

LayoutUnit RenderThemeDavinci::sliderTickSnappingThreshold() const
{
    return 5;
}

bool RenderThemeDavinci::supportsDataListUI(const AtomicString& type) const
{
    return type == InputTypeNames::range();
}
#endif

void RenderThemeDavinci::adjustInnerSpinButtonStyle(StyleResolver*, RenderStyle* style, Element*) const
{
    style->resetBorder();
    style->setWhiteSpace(PRE);

    int paddingTop = 0;
    int paddingLeft = 0;
    int paddingBottom = 0;
    int paddingRight = 0;
#if 0
    themeEngine()->getInnerSpinButtonPadding(paddingTop, paddingLeft, paddingBottom, paddingRight);
#endif
    style->setPaddingTop(Length(paddingTop, Fixed));
    style->setPaddingRight(Length(paddingRight, Fixed));
    style->setPaddingBottom(Length(paddingBottom, Fixed));
    style->setPaddingLeft(Length(paddingLeft, Fixed));
}

bool RenderThemeDavinci::paintInnerSpinButton(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
#if 0
    WebKit::WebThemeEngine::InnerSpinButtonExtraParams extraParams;
    extraParams.spinUp = isSpinUpButtonPartPressed(o);
    extraParams.readOnly = isReadOnlyControl(o);

    themeEngine()->paintInnerSpinButton(webCanvas(i), getWebThemeState(this, o), WebKit::WebRect(rect), extraParams);
#endif
    return false;
}

#if ENABLE(METER_ELEMENT)
void RenderThemeDavinci::adjustMeterStyle(StyleResolver*, RenderStyle* style, Element*) const
{
    style->setBoxShadow(nullptr);
}

IntSize RenderThemeDavinci::meterSizeForBounds(const RenderMeter*, const IntRect& bounds) const
{
    return bounds.size();
}

bool RenderThemeDavinci::supportsMeter(ControlPart part) const
{
    switch (part) {
    case RelevancyLevelIndicatorPart:
    case DiscreteCapacityLevelIndicatorPart:
    case RatingLevelIndicatorPart:
    case MeterPart:
    case ContinuousCapacityLevelIndicatorPart:
        return true;
    default:
        return false;
    }
}

bool RenderThemeDavinci::paintMeter(RenderObject* o, const PaintInfo& i, const IntRect& rect)
{
    if (!o->isMeter())
        return true;

#if 0
    RenderMeter* renderMeter = toRenderMeter(o);
    HTMLMeterElement* e = renderMeter->meterElement();
    WebKit::WebThemeEngine::MeterExtraParams extraParams;
    extraParams.min = e->min();
    extraParams.max = e->max();
    extraParams.value = e->value();
    extraParams.low = e->low();
    extraParams.high = e->high();
    extraParams.optimum = e->optimum();

    themeEngine()->paintMeter(webCanvas(i), getWebThemeState(this, o), rect, extraParams);
#endif

    return false;
}
#endif

}
