/*
** InspectorClient.h: InspectorClient implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#ifndef InspectorClientPS_H
#define InspectorClientPS_H

#include "InspectorClient.h"

namespace WebCore {

class InspectorClientPS : public InspectorClient
{
public:
    InspectorClientPS();
    virtual ~InspectorClientPS();

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
