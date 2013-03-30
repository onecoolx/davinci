/*
** RenderThemePS.h: RenderTheme implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef RenderThemePS_H
#define RenderThemePS_H

#include "RenderTheme.h"


namespace WebCore {


class RenderThemePS : public RenderTheme {
public:
    RenderThemePS();
    virtual ~RenderThemePS();

    // A method asking if the theme's controls actually care about redrawing when hovered.
    virtual bool supportsHover(const RenderStyle*) const;

    // A method to obtain the baseline position for a "leaf" control.  This will only be used if a baseline
    // position cannot be determined by examining child content. Checkboxes and radio buttons are examples of
    // controls that need to do this.
    virtual short baselinePosition(const RenderObject*) const;

    // A method asking if the control changes its tint when the window has focus or not.
    virtual bool controlSupportsTints(const RenderObject*) const;

    // A general method asking if any control tinting is supported at all.
    virtual bool supportsControlTints() const;

    virtual void adjustRepaintRect(const RenderObject*, IntRect&);

    virtual bool isControlStyled(const RenderStyle*, const BorderData&,
                                 const BackgroundLayer&, const Color& backgroundColor) const;

    virtual Color platformActiveSelectionBackgroundColor() const;
    virtual Color platformInactiveSelectionBackgroundColor() const;
    virtual Color platformActiveSelectionForegroundColor() const;
    virtual Color platformInactiveSelectionForegroundColor() const;

    // System fonts.
    virtual void systemFont(int propId, FontDescription&) const;

    virtual int minimumMenuListSize(RenderStyle*) const;

    virtual void adjustSliderThumbSize(RenderObject*) const;
    virtual void adjustSliderThumbStyle(CSSStyleSelector*, RenderStyle*, Element*) const; 
    
    virtual int popupInternalPaddingLeft(RenderStyle*) const;
    virtual int popupInternalPaddingRight(RenderStyle*) const;
    virtual int popupInternalPaddingTop(RenderStyle*) const;
    virtual int popupInternalPaddingBottom(RenderStyle*) const;

protected:
    // Methods for each appearance value.
    virtual bool paintCheckbox(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& r);
    virtual void setCheckboxSize(RenderStyle*) const;

    virtual bool paintRadio(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& r);
    virtual void setRadioSize(RenderStyle*) const;

    virtual void adjustButtonStyle(CSSStyleSelector*, RenderStyle*, Element*) const;
    virtual bool paintButton(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual void setButtonSize(RenderStyle*) const;

    virtual bool paintTextField(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual void adjustTextFieldStyle(CSSStyleSelector*, RenderStyle*, Element*) const;

    virtual bool paintTextArea(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual void adjustTextAreaStyle(CSSStyleSelector*, RenderStyle*, Element*) const;

    virtual bool paintMenuList(RenderObject* o, const RenderObject::PaintInfo& i, const IntRect& r);
    virtual void adjustMenuListStyle(CSSStyleSelector*, RenderStyle*, Element*) const;

    virtual bool paintMenuListButton(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual void adjustMenuListButtonStyle(CSSStyleSelector*, RenderStyle*, Element*) const;

    virtual bool paintSliderTrack(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual bool paintSliderThumb(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);

    virtual bool paintSearchField(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
    virtual void adjustSearchFieldStyle(CSSStyleSelector*, RenderStyle*, Element*) const;

    virtual void adjustSearchFieldCancelButtonStyle(CSSStyleSelector*, RenderStyle*, Element*) const;
    virtual bool paintSearchFieldCancelButton(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);

    virtual void adjustSearchFieldDecorationStyle(CSSStyleSelector*, RenderStyle*, Element*) const;
    virtual bool paintSearchFieldDecoration(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);

    virtual void adjustSearchFieldResultsDecorationStyle(CSSStyleSelector*, RenderStyle*, Element*) const;
    virtual bool paintSearchFieldResultsDecoration(RenderObject*, const RenderObject::PaintInfo&, const IntRect&);
private:
    unsigned int determineState(RenderObject* o);
    
};

};

#endif

