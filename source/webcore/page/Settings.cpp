/*
 * Copyright (C) 2006, 2007 Apple Computer, Inc.  All rights reserved.
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
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "Settings.h"

#include "Frame.h"
#include "FrameTree.h"
#include "Page.h"
#include "PageCache.h"
#include "HistoryItem.h"

namespace WebCore {

static void setNeedsReapplyStylesInAllFrames(Page* page)
{
	if (page){
		for (Frame* frame = page->mainFrame(); frame; frame = frame->tree()->traverseNext())
			frame->setNeedsReapplyStyles();
	}
}

EditableLinkBehavior Settings::m_editableLinkBehavior = EditableLinkDefaultBehavior;
int Settings::m_minimumFontSize = 0;
int Settings::m_minimumLogicalFontSize = 0;
int Settings::m_defaultFontSize = 0;
int Settings::m_defaultFixedFontSize = 0;
int Settings::m_scrollbarWidth = 0;
bool Settings::m_isJavaEnabled = false;
bool Settings::m_loadsImagesAutomatically = false;
bool Settings::m_privateBrowsingEnabled = false;
bool Settings::m_arePluginsEnabled = false;
bool Settings::m_isJavaScriptEnabled = false;
bool Settings::m_javaScriptCanOpenWindowsAutomatically = false;
bool Settings::m_shouldPrintBackgrounds = false;
bool Settings::m_textAreasAreResizable = false;
bool Settings::m_usesDashboardBackwardCompatibilityMode = false;
bool Settings::m_needsAdobeFrameReloadingQuirk = false;
bool Settings::m_isDOMPasteAllowed = false;
bool Settings::m_shrinksStandaloneImagesToFit = false;
bool Settings::m_usesPageCache = false;
bool Settings::m_showsURLsInToolTips = false;
bool Settings::m_forceFTPDirectoryListings = false;
bool Settings::m_developerExtrasEnabled = false;
bool Settings::m_autoDetectEncoding = false;
bool Settings::m_showAllAtOnce = false;
bool Settings::m_textAntialias = false;


String Settings::m_defaultTextEncodingName;
String Settings::m_ftpDirectoryTemplatePath;
KURL Settings::m_userStyleSheetLocation;
AtomicString Settings::m_standardFontFamily;
AtomicString Settings::m_fixedFontFamily;
AtomicString Settings::m_serifFontFamily;
AtomicString Settings::m_sansSerifFontFamily;
AtomicString Settings::m_cursiveFontFamily;
AtomicString Settings::m_fantasyFontFamily;

Settings * Settings::globalSettings(void)
{
	static Settings* settings = new Settings(0);
	settings->init();

	return settings;
}

void Settings::init(void)
{
    // A Frame may not have been created yet, so we initialize the AtomicString 
    // hash before trying to use it.
    AtomicString::init();

    static bool initialized = false;

    if (!initialized) {
        // setting up default value
        Settings::m_minimumFontSize = 0;
        Settings::m_minimumLogicalFontSize = 0;
        Settings::m_defaultFontSize = 14;
        Settings::m_defaultFixedFontSize = 14;
		Settings::m_scrollbarWidth = 16;
        Settings::m_loadsImagesAutomatically = true;
        Settings::m_arePluginsEnabled = true;
        Settings::m_isJavaScriptEnabled = true;
        Settings::m_javaScriptCanOpenWindowsAutomatically = false;
        Settings::m_shrinksStandaloneImagesToFit = true;
        Settings::m_shouldPrintBackgrounds = true;
        Settings::m_autoDetectEncoding = true;
        Settings::m_showAllAtOnce = false;
#if PLATFORM(WIN32)
		Settings::m_textAntialias = false;
#else
		Settings::m_textAntialias = true;
#endif
        Settings::m_textAreasAreResizable = false;
        Settings::m_isJavaEnabled = false;
        Settings::m_privateBrowsingEnabled = false;
        Settings::m_usesDashboardBackwardCompatibilityMode = false;
        Settings::m_needsAdobeFrameReloadingQuirk = false;
        Settings::m_isDOMPasteAllowed = false;
        Settings::m_usesPageCache = false;
        Settings::m_showsURLsInToolTips = false;
        Settings::m_forceFTPDirectoryListings = false;
        Settings::m_developerExtrasEnabled = false;

        Settings::m_standardFontFamily = AtomicString("Arial");
        Settings::m_sansSerifFontFamily = AtomicString("Arial");
        Settings::m_fixedFontFamily = AtomicString("Courier New");
        Settings::m_serifFontFamily = AtomicString("Times New Roman");
        Settings::m_defaultTextEncodingName = String("ISO8859-1");
        initialized = true;
    }
}

Settings::Settings(Page* page)
    : m_page(page)
{
}

void Settings::setStandardFontFamily(const AtomicString& standardFontFamily)
{
    if (standardFontFamily == Settings::m_standardFontFamily)
        return;

    Settings::m_standardFontFamily = standardFontFamily;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setFixedFontFamily(const AtomicString& fixedFontFamily)
{
    if (Settings::m_fixedFontFamily == fixedFontFamily)
        return;
        
    Settings::m_fixedFontFamily = fixedFontFamily;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setSerifFontFamily(const AtomicString& serifFontFamily)
{
    if (Settings::m_serifFontFamily == serifFontFamily)
        return;
        
    Settings::m_serifFontFamily = serifFontFamily;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setSansSerifFontFamily(const AtomicString& sansSerifFontFamily)
{
    if (Settings::m_sansSerifFontFamily == sansSerifFontFamily)
        return;
        
    Settings::m_sansSerifFontFamily = sansSerifFontFamily; 
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setCursiveFontFamily(const AtomicString& cursiveFontFamily)
{
    if (Settings::m_cursiveFontFamily == cursiveFontFamily)
        return;
        
    Settings::m_cursiveFontFamily = cursiveFontFamily;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setFantasyFontFamily(const AtomicString& fantasyFontFamily)
{
    if (Settings::m_fantasyFontFamily == fantasyFontFamily)
        return;
        
    Settings::m_fantasyFontFamily = fantasyFontFamily;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setMinimumFontSize(int minimumFontSize)
{
    if (Settings::m_minimumFontSize == minimumFontSize)
        return;

    Settings::m_minimumFontSize = minimumFontSize;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setMinimumLogicalFontSize(int minimumLogicalFontSize)
{
    if (Settings::m_minimumLogicalFontSize == minimumLogicalFontSize)
        return;

    Settings::m_minimumLogicalFontSize = minimumLogicalFontSize;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setDefaultFontSize(int defaultFontSize)
{
    if (Settings::m_defaultFontSize == defaultFontSize)
        return;

    Settings::m_defaultFontSize = defaultFontSize;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setDefaultFixedFontSize(int defaultFontSize)
{
    if (Settings::m_defaultFixedFontSize == defaultFontSize)
        return;

    Settings::m_defaultFixedFontSize = defaultFontSize;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setScrollBarWidth(int width)
{
	if (Settings::m_scrollbarWidth == width)
		return;

    Settings::m_scrollbarWidth = width;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setLoadsImagesAutomatically(bool loadsImagesAutomatically)
{
    Settings::m_loadsImagesAutomatically = loadsImagesAutomatically;
}

void Settings::setJavaScriptEnabled(bool isJavaScriptEnabled)
{
    Settings::m_isJavaScriptEnabled = isJavaScriptEnabled;
}

void Settings::setJavaEnabled(bool isJavaEnabled)
{
    Settings::m_isJavaEnabled = isJavaEnabled;
}

void Settings::setPluginsEnabled(bool arePluginsEnabled)
{
    Settings::m_arePluginsEnabled = arePluginsEnabled;
}

void Settings::setPrivateBrowsingEnabled(bool privateBrowsingEnabled)
{
    Settings::m_privateBrowsingEnabled = privateBrowsingEnabled;
}

void Settings::setJavaScriptCanOpenWindowsAutomatically(bool javaScriptCanOpenWindowsAutomatically)
{
    Settings::m_javaScriptCanOpenWindowsAutomatically = javaScriptCanOpenWindowsAutomatically;
}

void Settings::setDefaultTextEncodingName(const String& defaultTextEncodingName)
{
    Settings::m_defaultTextEncodingName = defaultTextEncodingName;
}

void Settings::setUserStyleSheetLocation(const KURL& userStyleSheetLocation)
{
    if (Settings::m_userStyleSheetLocation == userStyleSheetLocation)
        return;

    Settings::m_userStyleSheetLocation = userStyleSheetLocation;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setShouldPrintBackgrounds(bool shouldPrintBackgrounds)
{
    Settings::m_shouldPrintBackgrounds = shouldPrintBackgrounds;
}

void Settings::setTextAreasAreResizable(bool textAreasAreResizable)
{
    if (Settings::m_textAreasAreResizable == textAreasAreResizable)
        return;

    Settings::m_textAreasAreResizable = textAreasAreResizable;
    setNeedsReapplyStylesInAllFrames(m_page);
}

void Settings::setEditableLinkBehavior(EditableLinkBehavior editableLinkBehavior)
{
    Settings::m_editableLinkBehavior = editableLinkBehavior;
}

void Settings::setUsesDashboardBackwardCompatibilityMode(bool usesDashboardBackwardCompatibilityMode)
{
    Settings::m_usesDashboardBackwardCompatibilityMode = usesDashboardBackwardCompatibilityMode;
}

// FIXME: This quirk is needed because of Radar 4674537 and 5211271. We need to phase it out once Adobe
// can fix the bug from their end.
void Settings::setNeedsAdobeFrameReloadingQuirk(bool shouldNotReloadIFramesForUnchangedSRC)
{
    Settings::m_needsAdobeFrameReloadingQuirk = shouldNotReloadIFramesForUnchangedSRC;
}

void Settings::setDOMPasteAllowed(bool DOMPasteAllowed)
{
    Settings::m_isDOMPasteAllowed = DOMPasteAllowed;
}

void Settings::setUsesPageCache(bool usesPageCache)
{
    if (Settings::m_usesPageCache == usesPageCache)
        return;
        
    Settings::m_usesPageCache = usesPageCache;
    if (!Settings::m_usesPageCache) {
        HistoryItemVector& historyItems = m_page->backForwardList()->entries();
        for (unsigned i = 0; i < historyItems.size(); i++)
            pageCache()->remove(historyItems[i].get());
        pageCache()->releaseAutoreleasedPagesNow();
    }
}

void Settings::setShrinksStandaloneImagesToFit(bool shrinksStandaloneImagesToFit)
{
    Settings::m_shrinksStandaloneImagesToFit = shrinksStandaloneImagesToFit;
}

void Settings::setShowsURLsInToolTips(bool showsURLsInToolTips)
{
    Settings::m_showsURLsInToolTips = showsURLsInToolTips;
}

void Settings::setFTPDirectoryTemplatePath(const String& path)
{
    Settings::m_ftpDirectoryTemplatePath = path;
}

void Settings::setForceFTPDirectoryListings(bool force)
{
    Settings::m_forceFTPDirectoryListings = force;
}

void Settings::setDeveloperExtrasEnabled(bool developerExtrasEnabled)
{
    Settings::m_developerExtrasEnabled = developerExtrasEnabled;
}

void Settings::setAutoDetectEncoding(bool autoDetectEncoding) 
{ 
    Settings::m_autoDetectEncoding = autoDetectEncoding; 
}

void Settings::setShowAllAtOnce(bool showAllAtOnce) 
{ 
    Settings::m_showAllAtOnce = showAllAtOnce; 
}

void Settings::setTextAntialias(bool textAntialias)
{
	Settings::m_textAntialias = textAntialias;
}

} // namespace WebCore
