/*
 * Copyright (C) 2003, 2006 Apple Computer, Inc.  All rights reserved.
 *           (C) 2006 Graham Dennis (graham.dennis@gmail.com)
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

#ifndef Settings_h
#define Settings_h

#include "AtomicString.h"
#include "KURL.h"

namespace WebCore {

    class Page;

    enum EditableLinkBehavior {
        EditableLinkDefaultBehavior = 0,
        EditableLinkAlwaysLive,
        EditableLinkOnlyLiveWithShiftKey,
        EditableLinkLiveWhenNotFocused,
        EditableLinkNeverLive
    };

    class Settings
    {
    public:
        static void init(void);
		static Settings * globalSettings(void);
        Settings(Page*);

        void setStandardFontFamily(const AtomicString&);
        const AtomicString& standardFontFamily() const { return Settings::m_standardFontFamily; }

        void setFixedFontFamily(const AtomicString&);
        const AtomicString& fixedFontFamily() const { return Settings::m_fixedFontFamily; }

        void setSerifFontFamily(const AtomicString&);
        const AtomicString& serifFontFamily() const { return Settings::m_serifFontFamily; }

        void setSansSerifFontFamily(const AtomicString&);
        const AtomicString& sansSerifFontFamily() const { return Settings::m_sansSerifFontFamily; }

        void setCursiveFontFamily(const AtomicString&);
        const AtomicString& cursiveFontFamily() const { return Settings::m_cursiveFontFamily; }

        void setFantasyFontFamily(const AtomicString&);
        const AtomicString& fantasyFontFamily() const { return Settings::m_fantasyFontFamily; }

        void setMinimumFontSize(int);
        int minimumFontSize() const { return Settings::m_minimumFontSize; }

        void setMinimumLogicalFontSize(int);
        int minimumLogicalFontSize() const { return Settings::m_minimumLogicalFontSize; }

        void setDefaultFontSize(int);
        int defaultFontSize() const { return Settings::m_defaultFontSize; }

        void setDefaultFixedFontSize(int);
        int defaultFixedFontSize() const { return Settings::m_defaultFixedFontSize; }

		void setScrollBarWidth(int);
		int scrollBarWidth() const { return Settings::m_scrollbarWidth; }

        void setLoadsImagesAutomatically(bool);
        bool loadsImagesAutomatically() const { return Settings::m_loadsImagesAutomatically; }

        void setJavaScriptEnabled(bool);
        bool isJavaScriptEnabled() const { return Settings::m_isJavaScriptEnabled; }

        void setJavaScriptCanOpenWindowsAutomatically(bool);
        bool JavaScriptCanOpenWindowsAutomatically() const { return Settings::m_javaScriptCanOpenWindowsAutomatically; }

        void setJavaEnabled(bool);
        bool isJavaEnabled() const { return Settings::m_isJavaEnabled; }

        void setPluginsEnabled(bool);
        bool arePluginsEnabled() const { return Settings::m_arePluginsEnabled; }

        void setPrivateBrowsingEnabled(bool);
        bool privateBrowsingEnabled() const { return Settings::m_privateBrowsingEnabled; }
        
        void setDefaultTextEncodingName(const String&);
        const String& defaultTextEncodingName() const { return Settings::m_defaultTextEncodingName; }

        void setUserStyleSheetLocation(const KURL&);
        KURL userStyleSheetLocation() const { return Settings::m_userStyleSheetLocation; }

        void setShouldPrintBackgrounds(bool);
        bool shouldPrintBackgrounds() const { return Settings::m_shouldPrintBackgrounds; }

        void setTextAreasAreResizable(bool);
        bool textAreasAreResizable() const { return Settings::m_textAreasAreResizable; }

        void setEditableLinkBehavior(EditableLinkBehavior);
        EditableLinkBehavior editableLinkBehavior() const { return Settings::m_editableLinkBehavior; }
        
        void setUsesDashboardBackwardCompatibilityMode(bool);
        bool usesDashboardBackwardCompatibilityMode() const { return Settings::m_usesDashboardBackwardCompatibilityMode; }
        
        void setNeedsAdobeFrameReloadingQuirk(bool);
        bool needsAcrobatFrameReloadingQuirk() const { return Settings::m_needsAdobeFrameReloadingQuirk; }
        
        void setDOMPasteAllowed(bool);
        bool isDOMPasteAllowed() const { return Settings::m_isDOMPasteAllowed; }
        
        void setUsesPageCache(bool);
        bool usesPageCache() const { return Settings::m_usesPageCache; }

        void setShrinksStandaloneImagesToFit(bool);
        bool shrinksStandaloneImagesToFit() const { return Settings::m_shrinksStandaloneImagesToFit; }

        void setShowsURLsInToolTips(bool);
        bool showsURLsInToolTips() const { return Settings::m_showsURLsInToolTips; }

        void setFTPDirectoryTemplatePath(const String&);
        const String& ftpDirectoryTemplatePath() const { return Settings::m_ftpDirectoryTemplatePath; }
        
        void setForceFTPDirectoryListings(bool);
        bool forceFTPDirectoryListings() const { return Settings::m_forceFTPDirectoryListings; }
        
        void setDeveloperExtrasEnabled(bool);
        bool developerExtrasEnabled() const { return Settings::m_developerExtrasEnabled; }

        void setAutoDetectEncoding(bool); 
        bool autoDetectEncoding() const { return Settings::m_autoDetectEncoding; }

        void setShowAllAtOnce(bool); 
        bool showAllAtOnce() const { return Settings::m_showAllAtOnce; }

		void setTextAntialias(bool);
		bool textAntialias() const { return Settings::m_textAntialias; }

    private:
        Page* m_page;
        
        static String m_defaultTextEncodingName;
        static String m_ftpDirectoryTemplatePath;
        static KURL m_userStyleSheetLocation;
        static AtomicString m_standardFontFamily;
        static AtomicString m_fixedFontFamily;
        static AtomicString m_serifFontFamily;
        static AtomicString m_sansSerifFontFamily;
        static AtomicString m_cursiveFontFamily;
        static AtomicString m_fantasyFontFamily;
        static EditableLinkBehavior m_editableLinkBehavior;
        static int m_minimumFontSize;
        static int m_minimumLogicalFontSize;
        static int m_defaultFontSize;
        static int m_defaultFixedFontSize;
		static int m_scrollbarWidth;
        static bool m_isJavaEnabled;
        static bool m_loadsImagesAutomatically;
        static bool m_privateBrowsingEnabled;
        static bool m_arePluginsEnabled;
        static bool m_isJavaScriptEnabled;
        static bool m_javaScriptCanOpenWindowsAutomatically;
        static bool m_shouldPrintBackgrounds;
        static bool m_textAreasAreResizable;
        static bool m_usesDashboardBackwardCompatibilityMode;
        static bool m_needsAdobeFrameReloadingQuirk;
        static bool m_isDOMPasteAllowed;
        static bool m_shrinksStandaloneImagesToFit;
        static bool m_usesPageCache;
        static bool m_showsURLsInToolTips;
        static bool m_forceFTPDirectoryListings;
        static bool m_developerExtrasEnabled;
        static bool m_autoDetectEncoding;
        static bool m_showAllAtOnce;
		static bool m_textAntialias;
    };

} // namespace WebCore

#endif // Settings_h
