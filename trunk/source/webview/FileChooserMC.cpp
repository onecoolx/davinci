/*
** FileChooser.cpp: FileChooser implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "FileChooser.h"
#include "Document.h"
#include "FrameView.h"
#include "LocalizedStrings.h"
#include "Frame.h"
#include "Page.h"
#include "Icon.h"
#include "Frame.h"
#include "CString.h"

#include "WebCallback.h"

using namespace MaCross;

namespace WebCore {
    
FileChooser::FileChooser(FileChooserClient* client, const String& initialFilename)
    :m_client(client),m_filename(initialFilename)
    , m_icon(chooseIcon(initialFilename))
{
}

FileChooser::~FileChooser()
{
}

void FileChooser::openFileChooser(Document* document)
{
    static char  g_FileName[MC_PATH_MAX+1];
    memset(g_FileName, 0, MC_PATH_MAX+1);

    FrameView* view = document->view();
    if (!view)
        return;

    RefPtr<FileChooser> protector(this);
    if (cb_choose_file)
       if (cb_choose_file(g_FileName, MC_PATH_MAX, FALSE)) {
		   String name = String::fromUTF8(g_FileName);
           chooseFile(name);
	   }
}

String FileChooser::basenameForWidth(const Font& font, int width) const
{
     if (width <= 0)
         return String();

     String strToTruncate;
     if (m_filename.isEmpty()) 
         strToTruncate = fileButtonNoFileSelectedLabel(); 
     else
         strToTruncate = m_filename;

     if(width < (int)strToTruncate.length() )
        strToTruncate = strToTruncate.right(width);
 
     return strToTruncate;

}


}
