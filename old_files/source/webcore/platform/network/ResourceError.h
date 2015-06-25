// -*- mode: c++; c-basic-offset: 4 -*-
/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
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

#ifndef ResourceError_h
#define ResourceError_h

#include "PlatformString.h"

namespace WebCore {

    enum ResourceErrorType { NoType, HttpNetError, FtpNetError, CurlNetError};

    class ResourceError {
    public:
        ResourceError()
            : m_errorCode(0)
            , m_dataIsUpToDate(true)
            , m_isNull(true)
        {
        }

        ResourceError(const String& domain, int errorCode, const String& failingURL, const String& localizedDescription)
            : m_domain(domain)
            , m_errorCode(errorCode)
            , m_failingURL(failingURL)
            , m_localizedDescription(localizedDescription)
            , m_dataIsUpToDate(true)
            , m_isNull(false)
        {
        }

        ResourceError(int errorCode, const String& failingURL, ResourceErrorType type)
            : m_failingURL(failingURL)
            , m_dataIsUpToDate(false)
            , m_platformError(errorCode)
            , m_isNull(!errorCode)
            , m_type(type)
        {
        }

        bool isNull() const { return m_isNull; }

        const String& domain() const { unpackPlatformErrorIfNeeded(); return m_domain; }
        int errorCode() const { unpackPlatformErrorIfNeeded(); return m_errorCode; }
        const String& failingURL() const { unpackPlatformErrorIfNeeded(); return m_failingURL; }
        const String& localizedDescription() const { unpackPlatformErrorIfNeeded(); return m_localizedDescription; }

    private:
        void unpackPlatformErrorIfNeeded() const
        {
            if (!m_dataIsUpToDate)
                const_cast<ResourceError*>(this)->unpackPlatformError();
        }

        void unpackPlatformError();

        String m_domain;
        int m_errorCode;
        String m_failingURL;
        String m_localizedDescription;
 
        bool m_dataIsUpToDate;
        int m_platformError;
        bool m_isNull;
        ResourceErrorType m_type;
};

inline bool operator==(const ResourceError& a, const ResourceError& b)
{
    if (a.isNull() && b.isNull())
        return true;
    if (a.isNull() || b.isNull())
        return false;
    if (a.domain() != b.domain())
        return false;
    if (a.errorCode() != b.errorCode())
        return false;
    if (a.failingURL() != b.failingURL())
        return false;
    if (a.localizedDescription() != b.localizedDescription())
        return false;
    return true;
}

inline bool operator!=(const ResourceError& a, const ResourceError& b) { return !(a == b); }

} // namespace WebCore

#endif // ResourceError_h_
