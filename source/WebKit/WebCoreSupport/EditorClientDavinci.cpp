/*
 * EditorClientDavinci.cpp: EditorClientDavinci implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "EditorClientDavinci.h"

#include "Document.h"
#include "Editor.h"
#include "Frame.h"
#include "KeyboardEvent.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PlatformKeyboardEvent.h"
#include "Settings.h"
#include "UndoStep.h"
#if 0
#include "WebView.h"
#endif

using namespace WebCore;

namespace WebKit {

EditorClientDavinci::EditorClientDavinci(WebViewCore* core)
    : m_core(core)
{
}

EditorClientDavinci::~EditorClientDavinci()
{
}

void EditorClientDavinci::setInputMethodState(bool active)
{
    notImplemented();
}

bool EditorClientDavinci::shouldDeleteRange(Range*)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::isContinuousSpellCheckingEnabled()
{
    notImplemented();
    return false;
}

bool EditorClientDavinci::isGrammarCheckingEnabled()
{
    notImplemented();
    return false;
}

int EditorClientDavinci::spellCheckerDocumentTag()
{
    notImplemented();
    return 0;
}

bool EditorClientDavinci::shouldBeginEditing(WebCore::Range*)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::shouldEndEditing(WebCore::Range*)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::shouldInsertText(const String&, Range*, EditorInsertAction)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::shouldChangeSelectedRange(Range*, Range*, EAffinity, bool)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::shouldApplyStyle(WebCore::StylePropertySet*, WebCore::Range*)
{
    notImplemented();
    return true;
}

bool EditorClientDavinci::shouldMoveRangeAfterDelete(WebCore::Range*, WebCore::Range*)
{
    notImplemented();
    return true;
}

void EditorClientDavinci::didBeginEditing()
{
    notImplemented();
}

void EditorClientDavinci::respondToChangedContents()
{
    notImplemented();
}

void EditorClientDavinci::respondToChangedSelection(WebCore::Frame*)
{
    notImplemented();
}

void EditorClientDavinci::didEndEditing()
{
    notImplemented();
}

void EditorClientDavinci::didWriteSelectionToPasteboard()
{
    notImplemented();
}

void EditorClientDavinci::willWriteSelectionToPasteboard(WebCore::Range*)
{
    notImplemented();
}

void EditorClientDavinci::getClientPasteboardDataForRange(WebCore::Range*, Vector<String>&, Vector<RefPtr<WebCore::SharedBuffer> >&)
{
    notImplemented();
}

void EditorClientDavinci::didSetSelectionTypesForPasteboard()
{
    notImplemented();
}

void EditorClientDavinci::registerUndoStep(WTF::PassRefPtr<WebCore::UndoStep>)
{
    notImplemented();
}

void EditorClientDavinci::registerRedoStep(WTF::PassRefPtr<WebCore::UndoStep>)
{
    notImplemented();
}

void EditorClientDavinci::clearUndoRedoOperations()
{
    notImplemented();
}

bool EditorClientDavinci::canCopyCut(WebCore::Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool EditorClientDavinci::canPaste(WebCore::Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool EditorClientDavinci::canUndo() const
{
    notImplemented();
    return false;
}

bool EditorClientDavinci::canRedo() const
{
    notImplemented();
    return false;
}

void EditorClientDavinci::undo()
{
    notImplemented();
}

void EditorClientDavinci::redo()
{
    notImplemented();
}

bool EditorClientDavinci::shouldInsertNode(Node*, Range*, EditorInsertAction)
{
    notImplemented();
    return true;
}

void EditorClientDavinci::pageDestroyed()
{
    delete this;
}

bool EditorClientDavinci::smartInsertDeleteEnabled()
{
#if 0
    Page* page = m_webView->page();
    if (!page)
        return false;
    return page->settings().smartInsertDeleteEnabled();
#else
	return false;
#endif
}

bool EditorClientDavinci::isSelectTrailingWhitespaceEnabled()
{
#if 0
    Page* page = m_webView->page();
    if (!page)
        return false;
    return page->settings().selectTrailingWhitespaceEnabled();
#else
	return false;
#endif
}

void EditorClientDavinci::toggleContinuousSpellChecking()
{
    notImplemented();
}

void EditorClientDavinci::toggleGrammarChecking()
{
    notImplemented();
}

static const unsigned CtrlKey = 1 << 0;
static const unsigned AltKey = 1 << 1;
static const unsigned ShiftKey = 1 << 2;

struct KeyDownEntry {
    unsigned virtualKey;
    unsigned modifiers;
    const char* name;
};

struct KeyPressEntry {
    unsigned charCode;
    unsigned modifiers;
    const char* name;
};

#if 0
static const KeyDownEntry keyDownEntries[] = {
    { VK_LEFT,   0,                  "MoveLeft"                                    },
    { VK_LEFT,   ShiftKey,           "MoveLeftAndModifySelection"                  },
    { VK_LEFT,   CtrlKey,            "MoveWordLeft"                                },
    { VK_LEFT,   CtrlKey | ShiftKey, "MoveWordLeftAndModifySelection"              },
    { VK_RIGHT,  0,                  "MoveRight"                                   },
    { VK_RIGHT,  ShiftKey,           "MoveRightAndModifySelection"                 },
    { VK_RIGHT,  CtrlKey,            "MoveWordRight"                               },
    { VK_RIGHT,  CtrlKey | ShiftKey, "MoveWordRightAndModifySelection"             },
    { VK_UP,     0,                  "MoveUp"                                      },
    { VK_UP,     ShiftKey,           "MoveUpAndModifySelection"                    },
    { VK_PRIOR,  ShiftKey,           "MovePageUpAndModifySelection"                },
    { VK_DOWN,   0,                  "MoveDown"                                    },
    { VK_DOWN,   ShiftKey,           "MoveDownAndModifySelection"                  },
    { VK_NEXT,   ShiftKey,           "MovePageDownAndModifySelection"              },
    { VK_PRIOR,  0,                  "MovePageUp"                                  },
    { VK_NEXT,   0,                  "MovePageDown"                                },
    { VK_HOME,   0,                  "MoveToBeginningOfLine"                       },
    { VK_HOME,   ShiftKey,           "MoveToBeginningOfLineAndModifySelection"     },
    { VK_HOME,   CtrlKey,            "MoveToBeginningOfDocument"                   },
    { VK_HOME,   CtrlKey | ShiftKey, "MoveToBeginningOfDocumentAndModifySelection" },

    { VK_END,    0,                  "MoveToEndOfLine"                             },
    { VK_END,    ShiftKey,           "MoveToEndOfLineAndModifySelection"           },
    { VK_END,    CtrlKey,            "MoveToEndOfDocument"                         },
    { VK_END,    CtrlKey | ShiftKey, "MoveToEndOfDocumentAndModifySelection"       },

    { VK_BACK,   0,                  "DeleteBackward"                              },
    { VK_BACK,   ShiftKey,           "DeleteBackward"                              },
    { VK_DELETE, 0,                  "DeleteForward"                               },
    { VK_BACK,   CtrlKey,            "DeleteWordBackward"                          },
    { VK_DELETE, CtrlKey,            "DeleteWordForward"                           },

    { 'B',       CtrlKey,            "ToggleBold"                                  },
    { 'I',       CtrlKey,            "ToggleItalic"                                },

    { VK_ESCAPE, 0,                  "Cancel"                                      },
    { VK_TAB,    0,                  "InsertTab"                                   },
    { VK_TAB,    ShiftKey,           "InsertBacktab"                               },
    { VK_RETURN, 0,                  "InsertNewline"                               },
    { VK_RETURN, CtrlKey,            "InsertNewline"                               },
    { VK_RETURN, AltKey,             "InsertNewline"                               },
    { VK_RETURN, AltKey | ShiftKey,  "InsertNewline"                               },

    // It's not quite clear whether clipboard shortcuts and Undo/Redo should be handled
    // in the application or in WebKit. We chose WebKit for now.
    { 'C',       CtrlKey,            "Copy"                                        },
    { 'V',       CtrlKey,            "Paste"                                       },
    { 'X',       CtrlKey,            "Cut"                                         },
    { 'A',       CtrlKey,            "SelectAll"                                   },
    { VK_INSERT, CtrlKey,            "Copy"                                        },
    { VK_DELETE, ShiftKey,           "Cut"                                         },
    { VK_INSERT, ShiftKey,           "Paste"                                       },
    { 'Z',       CtrlKey,            "Undo"                                        },
    { 'Z',       CtrlKey | ShiftKey, "Redo"                                        }
};

static const KeyPressEntry keyPressEntries[] = {
    { '\t',   0,                  "InsertTab"                                   },
    { '\t',   ShiftKey,           "InsertBacktab"                               },
    { '\r',   0,                  "InsertNewline"                               },
    { '\r',   CtrlKey,            "InsertNewline"                               },
    { '\r',   AltKey,             "InsertNewline"                               },
    { '\r',   AltKey | ShiftKey,  "InsertNewline"                               }
};
#endif

const char* EditorClientDavinci::interpretKeyEvent(const KeyboardEvent* event)
{
    ASSERT(event->type() == eventNames().keydownEvent || event->type() == eventNames().keypressEvent);

    static HashMap<int, const char*>* keyDownCommandsMap = 0;
    static HashMap<int, const char*>* keyPressCommandsMap = 0;

    if (!keyDownCommandsMap) {
        keyDownCommandsMap = new HashMap<int, const char*>;
        keyPressCommandsMap = new HashMap<int, const char*>;

#if 0
        for (size_t i = 0; i < WTF_ARRAY_LENGTH(keyDownEntries); ++i)
            keyDownCommandsMap->set(keyDownEntries[i].modifiers << 16 | keyDownEntries[i].virtualKey, keyDownEntries[i].name);

        for (size_t i = 0; i < WTF_ARRAY_LENGTH(keyPressEntries); ++i)
            keyPressCommandsMap->set(keyPressEntries[i].modifiers << 16 | keyPressEntries[i].charCode, keyPressEntries[i].name);
#endif
    }

    unsigned modifiers = 0;
    if (event->shiftKey())
        modifiers |= ShiftKey;
    if (event->altKey())
        modifiers |= AltKey;
    if (event->ctrlKey())
        modifiers |= CtrlKey;

    if (event->type() == eventNames().keydownEvent) {
        int mapKey = modifiers << 16 | event->keyCode();
        return mapKey ? keyDownCommandsMap->get(mapKey) : 0;
    }

    int mapKey = modifiers << 16 | event->charCode();
    return mapKey ? keyPressCommandsMap->get(mapKey) : 0;
}

bool EditorClientDavinci::handleEditingKeyboardEvent(KeyboardEvent* event)
{
    Node* node = event->target()->toNode();
    ASSERT(node);
    Frame* frame = node->document()->frame();
    ASSERT(frame);

    const PlatformKeyboardEvent* keyEvent = event->keyEvent();
    if (!keyEvent)
        return false;

    bool caretBrowsing = frame->settings().caretBrowsingEnabled();
#if 0
    if (caretBrowsing) {
        switch (keyEvent->windowsVirtualKeyCode()) {
        case VK_LEFT:
            frame->selection().modify(keyEvent->shiftKey() ? FrameSelection::AlterationExtend : FrameSelection::AlterationMove,
                    DirectionLeft,
                    keyEvent->ctrlKey() ? WordGranularity : CharacterGranularity,
                    UserTriggered);
            return true;
        case VK_RIGHT:
            frame->selection().modify(keyEvent->shiftKey() ? FrameSelection::AlterationExtend : FrameSelection::AlterationMove,
                    DirectionRight,
                    keyEvent->ctrlKey() ? WordGranularity : CharacterGranularity,
                    UserTriggered);
            return true;
        case VK_UP:
            frame->selection().modify(keyEvent->shiftKey() ? FrameSelection::AlterationExtend : FrameSelection::AlterationMove,
                    DirectionBackward,
                    keyEvent->ctrlKey() ? ParagraphGranularity : LineGranularity,
                    UserTriggered);
            return true;
        case VK_DOWN:
            frame->selection().modify(keyEvent->shiftKey() ? FrameSelection::AlterationExtend : FrameSelection::AlterationMove,
                    DirectionForward,
                    keyEvent->ctrlKey() ? ParagraphGranularity : LineGranularity,
                    UserTriggered);
            return true;
        }
    }
#endif

    Editor::Command command = frame->editor().command(interpretKeyEvent(event));

    if (keyEvent->type() == PlatformEvent::RawKeyDown) {
        // WebKit doesn't have enough information about mode to decide how commands that just insert text if executed via Editor should be treated,
        // so we leave it upon WebCore to either handle them immediately (e.g. Tab that changes focus) or let a keypress event be generated
        // (e.g. Tab that inserts a Tab character, or Enter).
        return !command.isTextInsertion() && command.execute(event);
    }

    if (command.execute(event))
        return true;

    // Don't insert null or control characters as they can result in unexpected behaviour
    if (event->charCode() < ' ')
        return false;

    // Don't insert anything if a modifier is pressed
    if (keyEvent->ctrlKey() || keyEvent->altKey())
        return false;

    return frame->editor().insertText(event->keyEvent()->text(), event);
}

void EditorClientDavinci::handleKeyboardEvent(KeyboardEvent* event)
{
    if (handleEditingKeyboardEvent(event))
        event->setDefaultHandled();
}

void EditorClientDavinci::handleInputMethodKeydown(KeyboardEvent* event)
{
    notImplemented();
}

void EditorClientDavinci::textFieldDidBeginEditing(Element*)
{
}

void EditorClientDavinci::textFieldDidEndEditing(Element*)
{
}

void EditorClientDavinci::textDidChangeInTextField(Element*)
{
}

bool EditorClientDavinci::doTextFieldCommandFromEvent(Element*, KeyboardEvent*)
{
    return false;
}

void EditorClientDavinci::textWillBeDeletedInTextField(Element*)
{
    notImplemented();
}

void EditorClientDavinci::textDidChangeInTextArea(Element*)
{
    notImplemented();
}

bool EditorClientDavinci::shouldEraseMarkersAfterChangeSelection(TextCheckingType) const
{
    return true;
}

void EditorClientDavinci::ignoreWordInSpellDocument(const String& text)
{
    notImplemented();
}

void EditorClientDavinci::learnWord(const String& text)
{
    notImplemented();
}

void EditorClientDavinci::checkSpellingOfString(const UChar* text, int length, int* misspellingLocation, int* misspellingLength)
{
    notImplemented();
}

String EditorClientDavinci::getAutoCorrectSuggestionForMisspelledWord(const String& inputWord)
{
    // This method can be implemented using customized algorithms for the particular browser.
    // Currently, it computes an empty string.
    return String();
}

void EditorClientDavinci::checkGrammarOfString(const UChar*, int, Vector<GrammarDetail>&, int*, int*)
{
    notImplemented();
}

void EditorClientDavinci::updateSpellingUIWithGrammarString(const String&, const GrammarDetail&)
{
    notImplemented();
}

void EditorClientDavinci::updateSpellingUIWithMisspelledWord(const String&)
{
    notImplemented();
}

void EditorClientDavinci::showSpellingUI(bool)
{
    notImplemented();
}

bool EditorClientDavinci::spellingUIIsShowing()
{
    notImplemented();
    return false;
}

void EditorClientDavinci::getGuessesForWord(const String& word, const String& context, WTF::Vector<String>& guesses)
{
    notImplemented();
}

void EditorClientDavinci::willSetInputMethodState()
{
    notImplemented();
}

} // namespace WebKit
