/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 * Copyright (C) 2003, 2010, 2013 Apple Inc. ALl rights reserved.
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
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef HTMLStyleElement_h
#define HTMLStyleElement_h

#include "HTMLElement.h"
#include "InlineStyleSheetOwner.h"

namespace WebCore {

class HTMLStyleElement;
class StyleSheet;

template<typename T> class EventSender;
typedef EventSender<HTMLStyleElement> StyleEventSender;

class HTMLStyleElement FINAL : public HTMLElement {
public:
    static PassRefPtr<HTMLStyleElement> create(const QualifiedName&, Document*, bool createdByParser);
    virtual ~HTMLStyleElement();

    bool scoped() const;
    void setScoped(bool);
    Element* scopingElement() const;
    bool isRegisteredAsScoped() const
    {
        // Note: We cannot rely on the 'scoped' attribute still being present when this method is invoked.
        // Therefore we cannot rely on scoped()!
        if (m_scopedStyleRegistrationState == NotRegistered)
            return false;
        return true;
    }

    CSSStyleSheet* sheet() const { return m_styleSheetOwner.sheet(); }

    bool disabled() const;
    void setDisabled(bool);

    void dispatchPendingEvent(StyleEventSender*);
    static void dispatchPendingLoadEvents();

private:
    HTMLStyleElement(const QualifiedName&, Document*, bool createdByParser);

    // overload from HTMLElement
    virtual void parseAttribute(const QualifiedName&, const AtomicString&) OVERRIDE;
    virtual InsertionNotificationRequest insertedInto(ContainerNode*) OVERRIDE;
    virtual void removedFrom(ContainerNode*) OVERRIDE;
    virtual void childrenChanged(bool changedByParser = false, Node* beforeChange = 0, Node* afterChange = 0, int childCountDelta = 0);

    virtual void finishParsingChildren();

    virtual bool isLoading() const { return m_styleSheetOwner.isLoading(); }
    virtual bool sheetLoaded() { return m_styleSheetOwner.sheetLoaded(document()); }
    virtual void notifyLoadedSheetAndAllCriticalSubresources(bool errorOccurred);
    virtual void startLoadingDynamicSheet() { m_styleSheetOwner.startLoadingDynamicSheet(document()); }

    virtual void addSubresourceAttributeURLs(ListHashSet<KURL>&) const;

    void scopedAttributeChanged(bool);
    void registerWithScopingNode(bool);
    void unregisterWithScopingNode(ContainerNode*);

    InlineStyleSheetOwner m_styleSheetOwner;
    bool m_firedLoad;
    bool m_loadedSheet;

    enum ScopedStyleRegistrationState {
        NotRegistered,
        RegisteredAsScoped,
        RegisteredInShadowRoot
    };
    ScopedStyleRegistrationState m_scopedStyleRegistrationState;
};

inline bool isHTMLStyleElement(const Node* node)
{
    return node->hasTagName(HTMLNames::styleTag);
}

inline bool isHTMLStyleElement(const Element* element)
{
    return element->hasTagName(HTMLNames::styleTag);
}

inline HTMLStyleElement* toHTMLStyleElement(Node* node)
{
    ASSERT_WITH_SECURITY_IMPLICATION(!node || isHTMLStyleElement(node));
    return static_cast<HTMLStyleElement*>(node);
}

template <> inline bool isElementOfType<HTMLStyleElement>(const Element* element) { return isHTMLStyleElement(element); }

} //namespace

#endif