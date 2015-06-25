
#include "config.h"
#include "Pasteboard.h"
#include "DocumentFragment.h"
#include "Editor.h"
#include "markup.h"
#include "PlatformString.h"
#include "CString.h"
#include "Debug.h"

#include "WebCallback.h"

using namespace MaCross;

namespace WebCore {

Pasteboard::Pasteboard()
{
}

Pasteboard::~Pasteboard()
{
}

Pasteboard* Pasteboard::generalPasteboard()
{
    static Pasteboard* pasteboard = new Pasteboard;
    return pasteboard;
}

void Pasteboard::writeSelection(Range* selectedRange, bool canSmartCopyOrDelete, Frame* frame)
{
    //FIXME: selectedRange->toHTML() can get html code but now not used.
	if (cb_clipboard_set_data)
    	cb_clipboard_set_data((void*)selectedRange->text().utf8().data(), 
										selectedRange->text().utf8().length());
}

void Pasteboard::writeURL(const KURL& url, const String& title, Frame*)
{
    //FIXME: this is a simple implements.
	if (cb_clipboard_set_data)
    	cb_clipboard_set_data((void*)url.url().utf8().data(), url.url().utf8().length());
}

void Pasteboard::writeImage(Node*, const KURL&, const String& title)
{
    notImplemented()
}

void Pasteboard::clear()
{
    notImplemented()
}

bool Pasteboard::canSmartReplace()
{
    notImplemented()
    return false;
}

PassRefPtr<DocumentFragment> Pasteboard::documentFragment(Frame* frame, PassRefPtr<Range> context, bool allowPlainText, bool& chosePlainText)
{
    chosePlainText = false;
    size_t size = 0;
	if (cb_clipboard_data_len)
		size = cb_clipboard_data_len();

    if (size && cb_clipboard_get_data) {
        char *buffer = new char[size+1];
        memset(buffer, 0, sizeof(size+1));
        size_t get_size = cb_clipboard_get_data(buffer, size);
        String html = String::fromUTF8(buffer, get_size);
        if (! html.isEmpty()) {
            RefPtr<DocumentFragment> fragment = createFragmentFromMarkup(frame->document(), html, "");
            if (fragment)
                return fragment.release();
        }
        
        if (!allowPlainText)
            return 0;
        
        chosePlainText = true;
        RefPtr<DocumentFragment> fragment = createFragmentFromText(context.get(), html);
        if (fragment)
            return fragment.release();
        delete[] buffer;
    }
    return 0;
}

String Pasteboard::plainText(Frame*)
{
    size_t size = 0;
	if (cb_clipboard_data_len)
		size = cb_clipboard_data_len();

    if (size && cb_clipboard_get_data) {
        char *buffer = new char[size+1];
		memset(buffer, 0, size+1);
        size_t get_size = cb_clipboard_get_data(buffer, size);
        String str = String::fromUTF8(buffer, get_size);
		delete [] buffer;
		return str;
    }
    return String();
}

}
