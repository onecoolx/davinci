/*
** DragClient.h: DragClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef DragClientMC_H
#define DragClientMC_H

#include "DragClient.h"

namespace WebCore {

class DragClientMC : public DragClient
{
public:
    DragClientMC();
    virtual ~DragClientMC();

    virtual void dragControllerDestroyed(){delete this;}

    virtual void willPerformDragDestinationAction(DragDestinationAction, DragData*);
    virtual void willPerformDragSourceAction(DragSourceAction, const IntPoint&, Clipboard*);
    virtual DragDestinationAction actionMaskForDrag(DragData*);
    virtual DragSourceAction dragSourceActionMaskForPoint(const IntPoint& windowPoint);

    virtual void startDrag(DragImageRef dragImage, const IntPoint& dragImageOrigin, 
                                    const IntPoint& eventPos, Clipboard*, Frame*, bool linkDrag = false);
    virtual DragImageRef createDragImageForLink(KURL&, const String& label, Frame*);
};

}
#endif // DragClientMg_H
