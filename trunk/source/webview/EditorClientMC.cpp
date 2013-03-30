/*
** EditorClient.cpp: EditorClient implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include <wtf/HashMap.h>
#include "Frame.h"
#include "Page.h"
#include "FocusController.h"
#include "EditorClientMC.h"
#include "Document.h"
#include "Editor.h"
#include "KeyboardEvent.h"
#include "PlatformKeyboardEvent.h"
#include "ScanCodeMap.h"
#include "CString.h"
#include "EditCommand.h"

#include "WebView.h"
#include "WebEngine.h"
#include "WebCallback.h"
#include "Debug.h"

namespace WebCore {

static HashMap<unsigned int, const char*>* commandsMap = NULL;

EditorClientMC::EditorClientMC(_mc_view *view)
    :m_webview(view)
{
    if (!commandsMap) {
        commandsMap = new HashMap<unsigned int, const char*>;
        for (size_t i = 0; i < (sizeof(keyEntries)/sizeof(keyEntries[0])); i++)
            commandsMap->set(keyEntries[i].modifiers << 16 | keyEntries[i].virtualKey, keyEntries[i].name);
    }
}

EditorClientMC::~EditorClientMC() 
{
}

bool EditorClientMC::isEditable()
{
    return false;
}

bool EditorClientMC::shouldChangeSelectedRange(Range* fromRange, Range* toRange, EAffinity, bool stillSelecting)
{
    return true;
}

bool EditorClientMC::shouldDeleteRange(Range*)
{
    return true;
}

bool EditorClientMC::shouldBeginEditing(Range*)
{
    return true;
}

bool EditorClientMC::shouldEndEditing(Range*)
{
    return true;
}

bool EditorClientMC::shouldInsertText(String, Range*, EditorInsertAction)
{
    return true;
}

bool EditorClientMC::shouldApplyStyle(CSSStyleDeclaration*,Range*)
{
    return true;
}

bool EditorClientMC::shouldMoveRangeAfterDelete(Range*, Range*)
{
    return true;
}

bool EditorClientMC::shouldInsertNode(Node*, Range*, EditorInsertAction)
{
    return true;
}

void EditorClientMC::setInputMethodState(bool enabled)
{
	int ret = enabled ? 1 : 0;
	if (cb_set_ime_enable) 
		cb_set_ime_enable(ret);
}

static const char * translate_key_event (const PlatformKeyboardEvent* keyEvent)
{
    unsigned modifiers = 0;
    if (keyEvent->shiftKey())
        modifiers |= ShiftKey;
    if (keyEvent->altKey())
        modifiers |= AltKey;
    if (keyEvent->ctrlKey())
        modifiers |= CtrlKey;

    return commandsMap->get(modifiers << 16 | keyEvent->WindowsKeyCode());
}

void EditorClientMC::handleInputMethodKeypress(KeyboardEvent* event)
{
    handleKeypress(event);
}

void EditorClientMC::handleKeypress(KeyboardEvent* event)
{
    Frame* frame = m_webview->view->mainframe()->page()->focusController()->focusedOrMainFrame();
    if (!frame || !frame->document()->focusedNode())
        return;

    const PlatformKeyboardEvent* kevent = event->keyEvent();
    if (kevent->isKeyUp())
        return;

    Node* start = frame->selectionController()->start().node();
    if (!start)
        return;

    Node* focus = frame->document()->focusedNode();

    if (start->isContentEditable()) {
        String command(translate_key_event(kevent));
        if (command.isEmpty())
            return;
        if (focus->renderer() && focus->renderer()->isTextField() && (command == "MoveUp" || command == "MoveDown")) 
            return;
        frame->editor()->execCommand(command);
    }
    event->setDefaultHandled();
}

void EditorClientMC::respondToChangedSelection()
{
    Frame* frame = m_webview->view->mainframe()->page()->focusController()->focusedOrMainFrame();
    if (!frame || !frame->editor()->hasComposition())
        return;
    
    if (frame->editor()->ignoreCompositionSelectionChange())
        return;

    unsigned start;
    unsigned end;
    if (!frame->editor()->getCompositionSelection(start, end))
        frame->editor()->confirmCompositionWithoutDisturbingSelection();
}


//not implements
bool EditorClientMC::shouldShowDeleteInterface(HTMLElement*){notImplemented() return false;}
bool EditorClientMC::smartInsertDeleteEnabled(){notImplemented() return false;} 
bool EditorClientMC::isContinuousSpellCheckingEnabled(){notImplemented() return false;}
void EditorClientMC::toggleContinuousSpellChecking(){notImplemented() }
bool EditorClientMC::isGrammarCheckingEnabled(){notImplemented() return false;}
void EditorClientMC::toggleGrammarChecking(){notImplemented() }
int EditorClientMC::spellCheckerDocumentTag(){notImplemented() return 0;}
void EditorClientMC::didBeginEditing(){notImplemented() }
void EditorClientMC::respondToChangedContents(){notImplemented() }
void EditorClientMC::didEndEditing(){notImplemented() }
void EditorClientMC::didWriteSelectionToPasteboard(){notImplemented() }
void EditorClientMC::didSetSelectionTypesForPasteboard(){notImplemented() }
void EditorClientMC::registerCommandForUndo(PassRefPtr<WebCore::EditCommand>){notImplemented() }
void EditorClientMC::registerCommandForRedo(PassRefPtr<WebCore::EditCommand>){notImplemented() }
void EditorClientMC::clearUndoRedoOperations(){notImplemented() }
bool EditorClientMC::canUndo() const{notImplemented() return false;}
bool EditorClientMC::canRedo() const{notImplemented() return false;}
void EditorClientMC::undo(){notImplemented() }
void EditorClientMC::redo(){notImplemented() }
void EditorClientMC::textFieldDidBeginEditing(Element*){notImplemented() }
void EditorClientMC::textFieldDidEndEditing(Element*){notImplemented() }
void EditorClientMC::textDidChangeInTextField(Element*){notImplemented() }
bool EditorClientMC::doTextFieldCommandFromEvent(Element*, KeyboardEvent*){notImplemented() return false;}
void EditorClientMC::textWillBeDeletedInTextField(Element*){notImplemented() }
void EditorClientMC::textDidChangeInTextArea(Element*){notImplemented() }
void EditorClientMC::ignoreWordInSpellDocument(const String&){notImplemented() }
void EditorClientMC::learnWord(const String&){notImplemented() }
void EditorClientMC::checkSpellingOfString(const UChar*, int length, int* misspellingLocation, int* misspellingLength){notImplemented() }
void EditorClientMC::checkGrammarOfString(const UChar*, int length, Vector<GrammarDetail>&, int* badGrammarLocation, int* badGrammarLength){notImplemented() }
void EditorClientMC::updateSpellingUIWithGrammarString(const String&, const GrammarDetail& detail){notImplemented() }
void EditorClientMC::updateSpellingUIWithMisspelledWord(const String&){notImplemented() }
void EditorClientMC::showSpellingUI(bool show){notImplemented() }
bool EditorClientMC::spellingUIIsShowing(){notImplemented() return false;}
void EditorClientMC::getGuessesForWord(const String&, Vector<String>& guesses){notImplemented() }
}
