/*
 * KeyGenDavinci.cpp: KeyGen implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#include "AXObjectCache.h"
#include "CookieStorage.h"
#include "Editor.h"
#include "FTPDirectoryDocument.h"
#include "FrameView.h"
#include "KURL.h"
#include "NotImplemented.h"
#include "PluginView.h"
#include "ScrollbarTheme.h"
#include "SharedBuffer.h"

namespace WebCore {

void getSupportedKeySizes(Vector<String>&)
{
    notImplemented();
}

String signedPublicKeyAndChallengeString(unsigned, const String&, const KURL&)
{
    return String();
}

}

