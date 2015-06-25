
#ifndef ClipboardPlatform_H
#define ClipboardPlatform_H

#include "Clipboard.h"
#include "ClipboardAccessPolicy.h"

namespace WebCore {

class CachedImage;

// State available during IE's events for drag and drop and copy/paste
class ClipboardPlatform : public Clipboard 
{
public:
    ClipboardPlatform(ClipboardAccessPolicy policy, bool forDragging);
    virtual ~ClipboardPlatform();

    void clearData(const String& type);
    void clearAllData();
    String getData(const String& type, bool& success) const;
    bool setData(const String& type, const String& data);
    
    // extensions beyond IE's API
    HashSet<String> types() const;

    IntPoint dragLocation() const;
    CachedImage* dragImage() const;
    void setDragImage(CachedImage*, const IntPoint&);
    Node* dragImageElement();
    void setDragImageElement(Node*, const IntPoint&);

    virtual DragImageRef createDragImage(IntPoint& dragLoc) const;
    virtual void declareAndWriteDragImage(Element*, const KURL&, const String& title, Frame*);
    virtual void writeURL(const KURL&, const String&, Frame*);
    virtual void writeRange(Range*, Frame*);

    virtual bool hasData();
};

}

#endif // ClipboardMg_H
