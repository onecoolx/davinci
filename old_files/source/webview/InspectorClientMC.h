/*
** InspectorClient.h: InspectorClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#ifndef InspectorClientMC_H
#define InspectorClientMC_H

#include "InspectorClient.h"

namespace WebCore {

class InspectorClientMC : public InspectorClient
{
public:
    InspectorClientMC();
    virtual ~InspectorClientMC();

    virtual void inspectorDestroyed(){delete this;}

    virtual Page* createPage();

    virtual void showWindow();
    virtual void closeWindow();

    virtual void attachWindow();
    virtual void detachWindow();

    virtual void highlight(Node*);
    virtual void hideHighlight();

    virtual void inspectedURLChanged(const String& newURL);
};

}
#endif
