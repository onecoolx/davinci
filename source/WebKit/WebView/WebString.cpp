/*
 * WebString.cpp: WebString implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#include "WebCommon.h"
#include "WebObject.h"
#include "WebData.h"
#include "WebString.h"

#include <stdio.h>
#include <stdarg.h>
#include <wtf/text/StringImpl.h>
#include <wtf/unicode/UTF8.h>
#include <wtf/unicode/Unicode.h>

namespace davinci {

class WebStringImpl : public WTF::StringImpl
{
};

WebString::WebString()
    : m_impl(0)
{
}

WebString::~WebString()
{
    if (m_impl)
        m_impl->deref();
}

WebString::WebString(const char* s)
    : m_impl(0)
{
    RefPtr<StringImpl> string = WTF::StringImpl::create(s);
    m_impl = static_cast<WebStringImpl*>(string.get());
    m_impl->ref();
}

WebString::WebString(const UChar* s, unsigned int len)
    : m_impl(0)
{
    RefPtr<StringImpl> string = WTF::StringImpl::create(s, len);
    m_impl = static_cast<WebStringImpl*>(string.get());
    m_impl->ref();
}

WebString::WebString(WebStringImpl* impl)
    : m_impl(impl)
{
    m_impl->ref();
}

WebString::WebString(const WebString& o)
{
    if (o.m_impl)
        o.m_impl->ref();

    m_impl = o.m_impl;
}

WebString& WebString::operator=(const WebString& o)
{
    if (this == &o)
        return *this;

    if (o.m_impl)
        o.m_impl->ref();

    if (m_impl)
        m_impl->deref();

    m_impl = o.m_impl;
    return *this;
}

WebStringImpl* WebString::impl(void) const
{
    return m_impl;
}

const UChar* WebString::data(void) const
{
    return m_impl ? const_cast<WebStringImpl*>(m_impl)->characters() : 0;
}

UChar WebString::operator[](unsigned int index) const
{
    if (!m_impl || index >= length())
        return 0;

    return m_impl->characters()[index];
}

unsigned int WebString::length(void) const
{
    return m_impl ? const_cast<WebStringImpl*>(m_impl)->length() : 0;
}

bool WebString::equals(const WebString& s) const
{
    return equal(m_impl, s.m_impl);
}

unsigned int WebString::hash(void) const
{
    return m_impl ? const_cast<WebStringImpl*>(m_impl)->hash() : 0;
}

bool WebString::isEmpty(void) const
{
    return !m_impl || !m_impl->length();
}

bool WebString::isNull(void) const
{
    return !m_impl;
}

WebString WebString::subString(unsigned int start, unsigned int len) const
{
    if (!m_impl)
        return WebString();

    return WebString(static_cast<WebStringImpl*>(m_impl->substring(start, len).get()));
}

WebString WebString::left(unsigned int len) const 
{ 
    return subString(0, len);
}

WebString WebString::right(unsigned int len) const 
{ 
    return subString(length() - len, len); 
}

static inline void putUTF8Triple(char*& buffer, UChar ch)
{
    // Helper to write a three-byte UTF-8 code point to the buffer, caller must check room is available.
    *buffer++ = static_cast<char>(((ch >> 12) & 0x0F) | 0xE0);
    *buffer++ = static_cast<char>(((ch >> 6) & 0x3F) | 0x80);
    *buffer++ = static_cast<char>((ch & 0x3F) | 0x80);
}

WebData WebString::utf8(void)
{
    unsigned int length = this->length();
    const UChar* characters = this->data();

    // Allocate a buffer big enough to hold all the characters
    // (an individual UTF-16 UChar can only expand to 3 UTF-8 bytes).
    // Optimization ideas, if we find this function is hot:
    //  * We could speculatively create a CStringBuffer to contain 'length' 
    //    characters, and resize if necessary (i.e. if the buffer contains
    //    non-ascii characters). (Alternatively, scan the buffer first for
    //    ascii characters, so we know this will be sufficient).
    //  * We could allocate a CStringBuffer with an appropriate size to
    //    have a good chance of being able to write the string into the
    //    buffer without reallocing (say, 1.5 x length).
    if (length > UINT_MAX / 3)
        return WebData();

    WTF::Vector<char, 1024> bufferVector(length * 3);

    char* buffer = bufferVector.data();
    WTF::Unicode::ConversionResult result = 
        WTF::Unicode::convertUTF16ToUTF8(&characters, characters + length, &buffer, buffer + bufferVector.size(), false);

    // Only produced from strict conversion.
    if (result == WTF::Unicode::sourceIllegal)
        return WebData();

    // Check for an unconverted high surrogate.
    if (result == WTF::Unicode::sourceExhausted) {
        // This should be one unpaired high surrogate. Treat it the same
        // was as an unpaired high surrogate would have been handled in
        // the middle of a string with non-strict conversion - which is
        // to say, simply encode it to UTF-8.
        // There should be room left, since one UChar hasn't been converted.
        putUTF8Triple(buffer, *characters);
    }

    return WebData((Byte*)bufferVector.data(), buffer - bufferVector.data());
}

bool WebString::startsWith(const WebString& str, bool caseSensitive)
{
    if (isNull() || str.isNull())
        return false;

    if (isEmpty() || str.isEmpty())
        return false;

    return m_impl->startsWith(str.m_impl, caseSensitive);
}

bool WebString::startsWith(const char* str, bool caseSensitive)
{
    return startsWith(WebString(str), caseSensitive);
}

bool WebString::startsWith(const UChar* str, unsigned int len, bool caseSensitive)
{
    return startsWith(WebString(str, len), caseSensitive);
}

bool WebString::endsWith(const WebString& str, bool caseSensitive)
{
    if (isNull() || str.isNull())
        return false;

    if (isEmpty() || str.isEmpty())
        return false;

    return m_impl->endsWith(str.m_impl, caseSensitive);
}

bool WebString::endsWith(const char* str, bool caseSensitive)
{
    return endsWith(WebString(str), caseSensitive);
}

bool WebString::endsWith(const UChar* str, unsigned int len, bool caseSensitive)
{
    return endsWith(WebString(str, len), caseSensitive);
}

int WebString::find(const WebString& str, unsigned int startPos, bool caseSensitive)
{
    if (isNull() || str.isNull())
        return -1; // not found

    if (isEmpty() || str.isEmpty())
        return -1; // not found

    if (caseSensitive) {
        return (int)m_impl->find(str.m_impl, startPos);
    } else {
        return (int)m_impl->findIgnoringCase(str.m_impl, startPos);
    }
}

int WebString::find(const char* str, unsigned int startPos, bool caseSensitive)
{
    return find(WebString(str), startPos, caseSensitive);
}

int WebString::find(const UChar* str, unsigned int len, unsigned int startPos, bool caseSensitive)
{
    return find(WebString(str, len), startPos, caseSensitive);
}

int WebString::rfind(const WebString& str, unsigned int startPos, bool caseSensitive)
{
    if (isNull() || str.isNull())
        return -1; // not found

    if (isEmpty() || str.isEmpty())
        return -1; // not found

    if (caseSensitive) {
        return (int)m_impl->reverseFind(str.m_impl, startPos);
    } else {
        return (int)m_impl->reverseFindIgnoringCase(str.m_impl, startPos);
    }
}

int WebString::rfind(const char* str, unsigned int startPos, bool caseSensitive)
{
    return rfind(WebString(str), startPos, caseSensitive);
}

int WebString::rfind(const UChar* str, unsigned int len, unsigned int startPos, bool caseSensitive)
{
    return rfind(WebString(str, len), startPos, caseSensitive);
}

WebString WebString::fromUTF8(const char* string)
{
    if (!string)
        return WebString();

    return fromUTF8(string, strlen(string));
}

WebString WebString::fromUTF8(const char* string, unsigned int len)
{
    if (!string)
        return WebString();

    UChar* buffer;
    WebString stringBuffer(static_cast<WebStringImpl*>(StringImpl::createUninitialized(len, buffer).get()));
    UChar* bufferEnd = buffer + len;

    // Try converting into the buffer.
    const char* stringCurrent = string;
    if (WTF::Unicode::convertUTF8ToUTF16(&stringCurrent, string + len, &buffer, bufferEnd) != WTF::Unicode::conversionOK)
        return WebString();

    // stringBuffer is full (the input must have been all ascii) so just return it!
    if (buffer == bufferEnd)
        return stringBuffer;

    // stringBuffer served its purpose as a buffer, copy the contents out into a new string.
    unsigned utf16Length = buffer - stringBuffer.data();
    return WebString(stringBuffer.data(), utf16Length);
}

WebString WebString::format(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    WTF::Vector<char, 256> buffer;

    // Do the format once to get the length.
    char ch;
    int result = vsnprintf(&ch, 1, format, args);
    // We need to call va_end() and then va_start() again here, as the
    // contents of args is undefined after the call to vsnprintf
    // according to http://man.cx/snprintf(3)
    //
    // Not calling va_end/va_start here happens to work on lots of
    // systems, but fails e.g. on 64bit Linux.
    va_end(args);
    va_start(args, format);

    if (result == 0)
        return WebString("");
    if (result < 0)
        return WebString();
    unsigned len = result;
    buffer.grow(len + 1);
    
    // Now do the formatting again, guaranteed to fit.
    vsnprintf(buffer.data(), buffer.size(), format, args);

    va_end(args);
    
    return WebString(static_cast<WebStringImpl*>(StringImpl::create(buffer.data(), len).get()));
}

bool WebString::append(const WebString& str)
{
    if (str.isNull() || str.isEmpty())
        return false;

    if (!isNull() && !isEmpty()) {
        UChar* data;
        if (str.length() > (UINT_MAX - length()))
            return false;

        WTF::RefPtr<StringImpl> newImpl = StringImpl::createUninitialized(length() + str.length(), data);
        memcpy(data, this->data(), length() * sizeof(UChar));
        memcpy(data + length(), str.data(), str.length() * sizeof(UChar));
        *this = WebString(static_cast<WebStringImpl*>(newImpl.get()));
        return true;
    } else {
        *this = str;
        return true;
    }
}

bool WebString::append(const char* str)
{
    return append(WebString(str));
}

bool WebString::append(const UChar* str, unsigned int len)
{
    return append(WebString(str, len));
}

bool WebString::insert(const WebString& str, unsigned int pos)
{
    if (str.isNull() || str.isEmpty())
        return false;

    if (isNull() || isEmpty()) {
        *this = str;
        return true;
    }

    if (pos > length()) {
        append(str);
        return true;
    }

    UChar* data;
    if (str.length() > (UINT_MAX - length()))
        return false;

    WTF::RefPtr<StringImpl> newImpl = StringImpl::createUninitialized(length() + str.length(), data);
    memcpy(data, this->data(), pos * sizeof(UChar));
    memcpy(data + pos, str.data(), str.length() * sizeof(UChar));
    memcpy(data + pos + str.length(), this->data() + pos, (length() - pos) * sizeof(UChar));
    *this = WebString(static_cast<WebStringImpl*>(newImpl.get()));
    return true;
}

bool WebString::insert(const char* str, unsigned int pos)
{
    return insert(WebString(str), pos);
}

bool WebString::insert(const UChar* str, unsigned int len, unsigned int pos)
{
    return insert(WebString(str, len), pos);
}

bool WebString::remove(unsigned int start, unsigned int len)
{
    if (isNull() || isEmpty())
        return false;

    if (start >= length())
        return false;

    if (len > (length() - start))
        len = length() - start;

    UChar* data;
    WTF::RefPtr<StringImpl> newImpl = StringImpl::createUninitialized(length() - len, data);
    memcpy(data, this->data(), start * sizeof(UChar));
    memcpy(data + start, this->data() + start + len, (length() - len - start) * sizeof(UChar));
    *this = WebString(static_cast<WebStringImpl*>(newImpl.get()));
    return true;
}

}
