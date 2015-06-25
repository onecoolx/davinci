/*
** ContextMenuClientMC.h: ContextMenuClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#ifndef ContextMenuClientMC_H
#define ContextMenuClientMC_H

#include "ContextMenuClient.h"
#include "HitTestResult.h"

namespace WebCore {
    class ContextMenu;

class ContextMenuClientMC : public ContextMenuClient
{
public:
        ContextMenuClientMC();
        virtual ~ContextMenuClientMC();

        virtual void contextMenuDestroyed(){delete this;}

        virtual void downloadURL(const KURL& url);
        virtual void lookUpInDictionary(Frame*);
        virtual void searchWithGoogle(const Frame*);
        virtual void speak(const String&);
        virtual void stopSpeaking();
};

}

#endif // ContextMenuClientMC_H
