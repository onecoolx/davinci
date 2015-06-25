/*
 * Copyright (C) 2006, 2007 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
#include "config.h"
#include "macross.h"
#include "ContextMenu.h"
#include "CSSComputedStyleDeclaration.h"
#include "CSSProperty.h"
#include "CSSPropertyNames.h"
#include "ContextMenuController.h"
#include "Document.h"
#include "Editor.h"
#include "CString.h"
#include "Frame.h"
#include "FrameView.h"
#include "FrameLoader.h"
#include "KURL.h"
#include "LocalizedStrings.h"
#include "Node.h"
#include "Page.h"
#include "ResourceRequest.h"
#include "SelectionController.h"
#include "TextIterator.h"

#include "WebCallback.h"
#include "WebEngine.h"
#include "WebView.h"

using namespace MaCross;

using namespace std;
using namespace WTF;
using namespace Unicode;

namespace WebCore {

ContextMenuController* ContextMenu::controller() const
{
    if (Node* node = m_hitTestResult.innerNonSharedNode())
        if (Frame* frame = node->document()->frame())
            if (Page* page = frame->page())
                return page->contextMenuController();
    return 0;
}

static bool selectionContainsPossibleWord(Frame* frame)
{
    // Current algorithm: look for a character that's not just a separator.
    for (TextIterator it(frame->selectionController()->toRange().get()); !it.atEnd(); it.advance()) {
        int length = it.length();
        const UChar* characters = it.characters();
        for (int i = 0; i < length; ++i)
            if (!(category(characters[i]) & (Separator_Space | Separator_Line | Separator_Paragraph)))
                return true;
    }
    return false;
}

void ContextMenu::populate()
{
    HitTestResult result = hitTestResult();
    
    Node* node = m_hitTestResult.innerNonSharedNode();
    if (!node)
        return;

    Frame* frame = node->document()->frame();
    if (!frame)
        return;

	IntPoint point = frame->view()->contentsToWindow(result.point());
    if (!result.isContentEditable()) {
        FrameLoader* loader = frame->loader();
        KURL linkURL = result.absoluteLinkURL();
        KURL imageURL = result.absoluteImageURL();
		if (!linkURL.isEmpty() || !imageURL.isEmpty() || result.isSelected()) {
			if (cb_context_menu) {
				DeprecatedCString lurl_str;
				DeprecatedCString murl_str;
				CString sel_text;
				MC_CONTEXT_MENU_DATA menu;
				memset(&menu, 0, sizeof(MC_CONTEXT_MENU_DATA));
        		if (!linkURL.isEmpty()) {
            		if (loader->canHandleRequest(ResourceRequest(linkURL))){
						lurl_str = linkURL.url().utf8();
						menu.type |= MENU_TYPE_LINK; 
						menu.link_url = lurl_str.data();
					}
        		} 

				if (!imageURL.isEmpty()) {
					murl_str = imageURL.url().utf8();
					menu.type |= MENU_TYPE_IMAGE; 
					menu.image_url = murl_str.data();
        		} 
			
				if (result.isSelected()) {
					String text = frame->selectedText(); 
					text.stripWhiteSpace();
					sel_text = text.utf8();
					menu.type |= MENU_TYPE_SELECT; 
					menu.text = sel_text.data();
				}

				menu.location.x = point.x();
				menu.location.y = point.y();
				cb_context_menu(frame->view()->containingView(), &menu);
			}
        } else {
			if (cb_context_menu) {
				MC_CONTEXT_MENU_DATA menu;
				menu.type = MENU_TYPE_NONE;
				menu.location.x = point.x();
				menu.location.y = point.y();
				menu.link_url = 0;
				menu.image_url = 0;
				menu.text = 0;
				cb_context_menu(frame->view()->containingView(), &menu);
			}
        }
    } else { // Make an editing context menu
        SelectionController* selectionController = frame->selectionController();
        bool inPasswordField = selectionController->isInPasswordField();

		if (cb_context_menu) {
			CString sel_text;
			DeprecatedCString lurl_str;
			MC_CONTEXT_MENU_DATA menu;
			memset(&menu, 0, sizeof(MC_CONTEXT_MENU_DATA));
			menu.type |= MENU_TYPE_EDIT;

			if (!inPasswordField) {
				FrameLoader* loader = frame->loader();
				KURL linkURL = result.absoluteLinkURL();
				if (!linkURL.isEmpty()) {
					if (loader->canHandleRequest(ResourceRequest(linkURL))) {
						lurl_str = linkURL.url().utf8();
						menu.type |= MENU_TYPE_LINK; 
						menu.link_url = lurl_str.data();
					}
				}

				if (result.isSelected() && !inPasswordField && selectionContainsPossibleWord(frame)) 
				{
					String text = frame->selectedText(); 
					sel_text = text.utf8();
					menu.type |= MENU_TYPE_SELECT; 
					menu.text = sel_text.data();
				}
			}
			menu.location.x = point.x();
			menu.location.y = point.y();
			cb_context_menu(frame->view()->containingView(), &menu);
		}
	}
}

void ContextMenu::addInspectElementItem()
{
    Node* node = m_hitTestResult.innerNonSharedNode();
    if (!node)
        return;

    Frame* frame = node->document()->frame();
    if (!frame)
        return;

    Page* page = frame->page();
    if (!page)
        return;

    if (!page->inspectorController())
        return;
	//FIXME: not support inspector now.
}


void ContextMenu::checkOrEnableIfNeeded()
{
}

}
