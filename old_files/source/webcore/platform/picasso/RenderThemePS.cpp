/*
** RenderThemePS.cpp: RenderTheme implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include <wtf/MathExtras.h>
#include "RenderThemePS.h"
#include "RenderWidget.h"
#include "Element.h"
#include "Color.h"
#include "AffineTransform.h"
#include "GraphicsContext.h"
#include "Debug.h"

#include <picasso.h>

// Generic state constants
#define TS_NORMAL    0x00
#define TS_HOVER     0x01
#define TS_ACTIVE    0x02
#define TS_DISABLED  0x04
#define TS_FOCUSED   0x08
#define TS_CHECKED   0x10

// Button constants
#define BP_BUTTON    1
#define BP_RADIO     2
#define BP_CHECKBOX  3

#define BTN_WIDTH       14
#define BTN_HEIGHT      14
#define BTN_DOWNARROW_WIDTH 16
#define BTN_DOWNARROW_HEIGHT 16

namespace WebCore {

static void drawButtonNormal (GraphicsContext*, const IntRect&);
static void drawButtonHover (GraphicsContext*, const IntRect&);
static void drawButtonFocused (GraphicsContext*, const IntRect&);
static void drawButtonPressed (GraphicsContext*, const IntRect&);
static void drawButtonDisabled (GraphicsContext*, const IntRect&);

RenderTheme* theme()
{
    static RenderThemePS *theme = NULL;
    if (!theme)
        theme = new RenderThemePS;
    return theme;
}

RenderThemePS::RenderThemePS()
{
}

RenderThemePS::~RenderThemePS()
{
}

bool RenderThemePS::supportsHover(const RenderStyle*) const
{
    return true;
}

short RenderThemePS::baselinePosition(const RenderObject* o) const
{
    if (o->style()->appearance() == CheckboxAppearance || o->style()->appearance() == RadioAppearance)
        return o->marginTop() + o->height() - 2;
    return RenderTheme::baselinePosition(o);
}

bool RenderThemePS::controlSupportsTints(const RenderObject* o) const
{
    if (!isEnabled(o))
        return false;

    // Checkboxes only have tint when checked.
    if (o->style()->appearance() == CheckboxAppearance)
        return isChecked(o);

    // For now assume other controls have tint if enabled.
    return true;
}

bool RenderThemePS::supportsControlTints() const
{
    return true;
}

void RenderThemePS::adjustRepaintRect(const RenderObject* o, IntRect& r)
{
    RenderTheme::adjustRepaintRect(o, r);
}

bool RenderThemePS::isControlStyled(const RenderStyle* style, const BorderData& border,
        const BackgroundLayer& background, const Color& backgroundColor) const
{
    if (style->appearance() == TextFieldAppearance || style->appearance() == TextAreaAppearance 
        || style->appearance() == ListboxAppearance)
        return style->border() != border;
    return RenderTheme::isControlStyled(style, border, background, backgroundColor);
}

Color RenderThemePS::platformActiveSelectionBackgroundColor() const
{
    return Color(0x62, 0x8C, 0xB2, 0xA0);
}

Color RenderThemePS::platformInactiveSelectionBackgroundColor() const
{
    return Color(0xB0, 0xB0, 0xB0, 0xA0);
}

Color RenderThemePS::platformActiveSelectionForegroundColor() const
{
    return Color(0xFF, 0xFF, 0xFF);
}

Color RenderThemePS::platformInactiveSelectionForegroundColor() const
{
    return Color(0xFF, 0xFF, 0xFF);
}

int RenderThemePS::minimumMenuListSize(RenderStyle* style) const
{
    return RenderTheme::minimumMenuListSize(style);
}

void RenderThemePS::adjustSliderThumbSize(RenderObject* o) const
{
    RenderTheme::adjustSliderThumbSize(o);
}

void RenderThemePS::adjustSliderThumbStyle(CSSStyleSelector* selecter, RenderStyle* style, Element* e) const
{
    RenderTheme::adjustSliderThumbStyle(selecter, style, e);
}

int RenderThemePS::popupInternalPaddingLeft(RenderStyle*) const
{
    return 0;
}

int RenderThemePS::popupInternalPaddingRight(RenderStyle*) const
{
    return 0;
}

int RenderThemePS::popupInternalPaddingTop(RenderStyle*) const
{
    return 0;
}

int RenderThemePS::popupInternalPaddingBottom(RenderStyle*) const
{
    return 0;
}

bool RenderThemePS::paintCheckbox(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
    ps_context* gc = i.context->platformContext();
    
    unsigned btnstate = determineState(o);
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_rectangle(gc, &r);
	ps_color s = {0, 0, 0, 0};
	ps_color f = {0, 0, 0, 0};
	ps_point p = {0, 0};

    if (btnstate & TS_CHECKED) {
        if (btnstate & TS_DISABLED) {
 			s.r = 0.50; s.g = 0.50; s.b = 0.50; s.a = 1.00;
 			f.r = 0.80; f.g = 0.80; f.b = 0.80; f.a = 1.00;
        } else {
 			s.r = 0.25; s.g = 0.75; s.b = 0.75; s.a = 1.00;
 			f.r = 0.90; f.g = 1.00; f.b = 1.00; f.a = 1.00;
		}
		p.x = r.x + 3; p.y = r.y + 3;
		ps_move_to (gc, &p);
		p.x = r.x + r.w - 3; p.y = r.y + r.h - 3;
		ps_line_to (gc, &p);

		p.x = r.x + r.w - 3; p.y = r.y + 3;
		ps_move_to (gc, &p);
		p.x = r.x + 3; p.y = r.y + r.h - 3;
		ps_line_to (gc, &p);

		ps_set_stroke_color(gc, &s);
		ps_set_source_color(gc, &f);
		ps_paint(gc);
    } else {
        if (btnstate & TS_DISABLED) {
 			s.r = 0.50; s.g = 0.50; s.b = 0.50; s.a = 1.00;
 			f.r = 0.80; f.g = 0.80; f.b = 0.80; f.a = 1.00;
		} else {
 			s.r = 0.25; s.g = 0.75; s.b = 0.75; s.a = 1.00;
 			f.r = 0.90; f.g = 1.00; f.b = 1.00; f.a = 1.00;
		}
		ps_set_stroke_color(gc, &s);
		ps_set_source_color(gc, &f);
		ps_paint(gc);
    }

    if (btnstate & TS_FOCUSED) { //focused
        i.context->addFocusRingRect(IntRect(rc.x(), rc.y(), rc.width(), rc.height()));
        i.context->drawFocusRing(Color(Color::darkGray));
        i.context->clearFocusRing();
    }
    return false;
}

void RenderThemePS::setCheckboxSize(RenderStyle* style) const
{
    // If the width and height are both specified, then we have nothing to do.
    if (!style->width().isIntrinsicOrAuto() && !style->height().isAuto())
        return;

    if (style->width().isIntrinsicOrAuto())
        style->setWidth(Length(BTN_WIDTH, Fixed));

    if (style->height().isAuto())
        style->setHeight(Length(BTN_HEIGHT, Fixed));
}

bool RenderThemePS::paintRadio(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
    ps_context *gc = i.context->platformContext();

    unsigned btnstate = determineState(o);
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_ellipse(gc, &r);
	ps_color s = {0, 0, 0, 0};
	ps_color f = {0, 0, 0, 0};

    if (btnstate & TS_CHECKED) {
        if (btnstate & TS_DISABLED) {
 			s.r = 0.50; s.g = 0.50; s.b = 0.50; s.a = 1.00;
 			f.r = 0.80; f.g = 0.80; f.b = 0.80; f.a = 1.00;
        } else {
 			s.r = 0.25; s.g = 0.75; s.b = 0.75; s.a = 1.00;
 			f.r = 0.90; f.g = 1.00; f.b = 1.00; f.a = 1.00;
		}
		ps_set_stroke_color(gc, &s);
		ps_set_source_color(gc, &f);
		ps_paint(gc);

		ps_rect rp = {rc.x()+5.5, rc.y()+5.5, rc.width()-9, rc.height()-9};
		ps_set_source_color(gc, &s);
		ps_ellipse(gc, &rp);
		ps_fill(gc);
    } else {
        if (btnstate & TS_DISABLED) {
 			s.r = 0.50; s.g = 0.50; s.b = 0.50; s.a = 1.00;
 			f.r = 0.80; f.g = 0.80; f.b = 0.80; f.a = 1.00;
		} else {
 			s.r = 0.25; s.g = 0.75; s.b = 0.75; s.a = 1.00;
 			f.r = 0.90; f.g = 1.00; f.b = 1.00; f.a = 1.00;
		}
		ps_set_stroke_color(gc, &s);
		ps_set_source_color(gc, &f);
		ps_paint(gc);
    }

    if (btnstate & TS_FOCUSED) { //focused
        i.context->addFocusRingRect(IntRect(rc.x(), rc.y(), rc.width(), rc.height()));
        i.context->drawFocusRing(Color(Color::darkGray));
        i.context->clearFocusRing();
    }
    return false;
}

void RenderThemePS::setRadioSize(RenderStyle* style) const
{
    // If the width and height are both specified, then we have nothing to do.
    if (!style->width().isIntrinsicOrAuto() && !style->height().isAuto())
        return;

    if (style->width().isIntrinsicOrAuto())
        style->setWidth(Length(BTN_WIDTH, Fixed));

    if (style->height().isAuto())
        style->setHeight(Length(BTN_HEIGHT, Fixed));
}

void RenderThemePS::adjustButtonStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    RenderTheme::adjustButtonStyle(selector, style, e);
}

void RenderThemePS::setButtonSize(RenderStyle* style) const
{
    RenderTheme::setButtonSize(style);
}

bool RenderThemePS::paintButton(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
    unsigned btnstate = determineState(o);
    
    if (btnstate & TS_ACTIVE) //pressed
        drawButtonPressed (i.context, rc);
    else if (btnstate & TS_DISABLED) //disabled
        drawButtonDisabled (i.context, rc);
    else if (btnstate & TS_HOVER) //hoverd
        drawButtonHover (i.context, rc);
    else
        drawButtonNormal (i.context, rc);

    if (btnstate & TS_FOCUSED) //focused
        drawButtonFocused (i.context, rc);
    return false;
}

void RenderThemePS::adjustTextFieldStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    RenderTheme::adjustTextFieldStyle(selector, style, e);
}

bool RenderThemePS::paintTextField(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
    ps_context *gc = i.context->platformContext();
	ps_rect r = {rc.x(), rc.y(), rc.width()-1, rc.height()-1};
	ps_rectangle(gc, &r);
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.90, 1.00, 1.00, 1.00};
	ps_set_stroke_color(gc, &s);
	ps_set_source_color(gc, &f);
	ps_paint(gc);
	return false;
}

void RenderThemePS::adjustTextAreaStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    RenderTheme::adjustTextAreaStyle(selector, style, e);
}

bool RenderThemePS::paintTextArea(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
	return paintTextField(o, i, rc);
}

bool RenderThemePS::paintMenuList(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
	ps_point p = {0 , 0};
    ps_context *gc = i.context->platformContext();
    unsigned btnstate = determineState(o);
	ps_rect r = {rc.x(), rc.y(), rc.width()-BTN_DOWNARROW_WIDTH, rc.height()};
	ps_rounded_rect(gc, &r, 5, 5, 0, 0, 5, 5, 0, 0);
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.90, 1.00, 1.00, 1.00};
	ps_set_stroke_color(gc, &s);
	ps_set_source_color(gc, &f);
	ps_paint(gc);

	ps_rect rb = {rc.x()+rc.width()-BTN_DOWNARROW_WIDTH, rc.y(), BTN_DOWNARROW_WIDTH, rc.height()};
	ps_rounded_rect(gc, &rb, 0, 0, 5, 5, 0, 0, 5, 5);
	ps_paint(gc);
	p.x = rb.x+3; p.y = rb.y+rb.h/2-2;
	ps_move_to(gc, &p);
	p.x = rb.x+rb.w/2; p.y = rb.y+rb.h/2+2;
	ps_line_to(gc, &p);
	p.x = rb.x+rb.w/2+4.5; p.y = rb.y+rb.h/2-2;
	ps_line_to(gc, &p);
	ps_stroke(gc);

    if (btnstate & TS_FOCUSED) { //focused
        i.context->addFocusRingRect(IntRect(rc.x(), rc.y(), rc.width(), rc.height()));
        i.context->drawFocusRing(Color(Color::darkGray));
        i.context->clearFocusRing();
    }
    return false;
}

void RenderThemePS::adjustMenuListStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    style->setMinHeight(Length(BTN_DOWNARROW_HEIGHT, Fixed));
    style->setPaddingRight(Length(BTN_DOWNARROW_WIDTH, Fixed));
}

bool RenderThemePS::paintMenuListButton(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& rc)
{
	ps_point p = {0 , 0};
    ps_context *gc = i.context->platformContext();
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.90, 1.00, 1.00, 1.00};
	ps_set_stroke_color(gc, &s);
	ps_set_source_color(gc, &f);
	ps_rect r = {rc.x()+rc.width()-BTN_DOWNARROW_WIDTH, rc.y(), BTN_DOWNARROW_WIDTH-1, rc.height()-1};
	ps_rounded_rect(gc, &r, 0, 0, 5, 5, 0, 0, 5, 5);
	ps_paint(gc);
	p.x = r.x+3; p.y = r.y+r.h/2-2;
	ps_move_to(gc, &p);
	p.x = r.x+r.w/2; p.y = r.y+r.h/2+2;
	ps_line_to(gc, &p);
	p.x = r.x+r.w/2+4; p.y = r.y+r.h/2-2;
	ps_line_to(gc, &p);
	ps_stroke(gc);
    return false;
}

void RenderThemePS::adjustMenuListButtonStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    style->setMinHeight(Length(BTN_DOWNARROW_HEIGHT, Fixed));
    style->setPaddingRight(Length(BTN_DOWNARROW_WIDTH, Fixed));
}

bool RenderThemePS::paintSliderTrack(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSliderTrack(o, pi, r);
}

bool RenderThemePS::paintSliderThumb(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSliderThumb(o, pi, r);
}

bool RenderThemePS::paintSearchField(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSearchField(o, pi, r);
}

void RenderThemePS::adjustSearchFieldStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    notImplemented();
    RenderTheme::adjustSearchFieldStyle(selector, style, e);
}

void RenderThemePS::adjustSearchFieldCancelButtonStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    notImplemented();
    RenderTheme::adjustSearchFieldCancelButtonStyle(selector, style, e);
}

bool RenderThemePS::paintSearchFieldCancelButton(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSearchFieldCancelButton(o, pi, r);
}

void RenderThemePS::adjustSearchFieldDecorationStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    notImplemented();
    RenderTheme::adjustSearchFieldDecorationStyle(selector, style, e);
}

bool RenderThemePS::paintSearchFieldDecoration(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSearchFieldDecoration(o, pi, r);
}

void RenderThemePS::adjustSearchFieldResultsDecorationStyle(CSSStyleSelector* selector, RenderStyle* style, Element* e) const
{
    notImplemented();
    RenderTheme::adjustSearchFieldResultsDecorationStyle(selector, style, e);
}

bool RenderThemePS::paintSearchFieldResultsDecoration(RenderObject* o, const RenderObject::PaintInfo& pi, const IntRect& r)
{
    notImplemented();
    return RenderTheme::paintSearchFieldResultsDecoration(o, pi, r);
}


void RenderThemePS::systemFont(int propId, FontDescription& fontDescription) const
{
    notImplemented();
}

unsigned RenderThemePS::determineState(RenderObject* o)
{
    unsigned result = TS_NORMAL;
    if (!isEnabled(o))
        result |= TS_DISABLED;
    else if (isPressed(o))
        result |= TS_ACTIVE;
    else if (isHovered(o))
        result |= TS_HOVER;
    
    if (supportsFocusRing(o->style()) && isFocused(o))
        result |= TS_FOCUSED;

    if (isChecked(o))
        result |= TS_CHECKED; 

    return result;
}
// static draw functions.
static void drawButtonNormal (GraphicsContext* context, const IntRect& rc)
{
    ps_context *gc = context->platformContext();
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.90, 1.00, 1.00, 1.00};
	ps_color e = {1.00, 1.00, 1.00, 1.00};
	ps_point sp = {r.x, r.y+r.h};
	ps_point ep = {r.x, r.y};
	ps_gradient* g = ps_gradient_create_linear(GRADIENT_SPREAD_PAD, &sp, &ep);
	ps_gradient_add_color_stop(g, 0.1, &f);
	ps_gradient_add_color_stop(g, 0.9, &e);

	ps_set_stroke_color(gc, &s);
	ps_set_source_gradient(gc, g);
	ps_rounded_rect(gc, &r, 3, 3, 3, 3, 3, 3, 3, 3);
	ps_paint(gc);
	ps_gradient_unref(g);
}

static void drawButtonHover (GraphicsContext* context, const IntRect& rc)
{
    ps_context *gc = context->platformContext();
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.98, 1.00, 1.00, 1.00};
	ps_set_stroke_color(gc, &s);
	ps_set_source_color(gc, &f);
	ps_rounded_rect(gc, &r, 3, 3, 3, 3, 3, 3, 3, 3);
	ps_paint(gc);
}

static void drawButtonFocused (GraphicsContext* context, const IntRect& rc)
{
#ifndef FOCUSRING_TV   
    context->addFocusRingRect(IntRect(rc.x()+4, rc.y()+4, rc.width()-8, rc.height()-8));
#else
    context->addFocusRingRect(rc);
#endif /* FOCUSRING_TV */
    context->drawFocusRing(Color(Color::darkGray));
    context->clearFocusRing();
}

static void drawButtonPressed (GraphicsContext* context, const IntRect& rc)
{
    ps_context *gc = context->platformContext();
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_color s = {0.25, 0.75, 0.75, 1.00};
	ps_color f = {0.75, 0.90, 0.90, 1.00};
	ps_color e = {0.90, 1.00, 1.00, 1.00};
	ps_point sp = {r.x, r.y+r.h};
	ps_point ep = {r.x, r.y};
	ps_gradient* g = ps_gradient_create_linear(GRADIENT_SPREAD_PAD, &sp, &ep);
	ps_gradient_add_color_stop(g, 0.1, &f);
	ps_gradient_add_color_stop(g, 0.9, &e);

	ps_set_stroke_color(gc, &s);
	ps_set_source_gradient(gc, g);
	ps_rounded_rect(gc, &r, 3, 3, 3, 3, 3, 3, 3, 3);
	ps_paint(gc);
	ps_gradient_unref(g);
}

static void drawButtonDisabled (GraphicsContext* context, const IntRect& rc)
{
    ps_context *gc = context->platformContext();
	ps_rect r = {rc.x()+1, rc.y()+1, rc.width()-2, rc.height()-2};
	ps_color s = {0.50, 0.50, 0.50, 1.00};
	ps_color f = {0.80, 0.80, 0.80, 1.00};
	ps_color e = {1.00, 1.00, 1.00, 1.00};
	ps_point sp = {r.x, r.y+r.h};
	ps_point ep = {r.x, r.y};
	ps_gradient* g = ps_gradient_create_linear(GRADIENT_SPREAD_PAD, &sp, &ep);
	ps_gradient_add_color_stop(g, 0.1, &f);
	ps_gradient_add_color_stop(g, 0.9, &e);

	ps_set_stroke_color(gc, &s);
	ps_set_source_gradient(gc, g);
	ps_rounded_rect(gc, &r, 3, 3, 3, 3, 3, 3, 3, 3);
	ps_paint(gc);
	ps_gradient_unref(g);
}

}

