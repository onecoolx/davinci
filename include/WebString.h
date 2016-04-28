/*
 * WebString.h: Unicode string implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_STRING_H_
#define _DAVINCI_STRING_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

/* UTF-16 string implement. */ 

class WebStringImpl;

class EXPORT_API WebString : public WebObject
{
public:
	WebString();
	WebString(const char* data);
	WebString(const UChar* data, unsigned int len);
	WebString(const WebString& o);
	WebString& operator=(const WebString& o);

	virtual ~WebString();
public:
	const UChar* data(void) const;
	unsigned int length(void) const;
	bool equals(const WebString& s) const;

	unsigned int hash(void) const;
	bool isEmpty(void) const;
	bool isNull(void) const;

	bool startsWith(const WebString& str, bool caseSensitive = true);
	bool startsWith(const char* str, bool caseSensitive = true);
	bool startsWith(const UChar* str, unsigned int len, bool caseSensitive = true);

	bool endsWith(const WebString& str, bool caseSensitive = true);
	bool endsWith(const char* str, bool caseSensitive = true);
	bool endsWith(const UChar* str, unsigned int len, bool caseSensitive = true);

	WebString subString(unsigned int start, unsigned int len = UINT_MAX) const;
    WebString left(unsigned int len) const;
    WebString right(unsigned int len) const;

	bool append(const WebString& str);
	bool append(const char* str);
	bool append(const UChar* str, unsigned int len);

	bool insert(const WebString& str, unsigned int pos);
	bool insert(const char* str, unsigned int pos);
	bool insert(const UChar* str, unsigned int len, unsigned int pos);

	bool remove(unsigned int start, unsigned int len);

	int find(const WebString& str, unsigned int startPos = 0, bool caseSensitive = true);
	int find(const char* str, unsigned int startPos = 0, bool caseSensitive = true);
	int find(const UChar* str, unsigned int len, unsigned int startPos = 0, bool caseSensitive = true);
	
	int rfind(const WebString& str, unsigned int startPos = UINT_MAX, bool caseSensitive = true);
	int rfind(const char* str, unsigned int startPos = UINT_MAX, bool caseSensitive = true);
	int rfind(const UChar* str, unsigned int len, unsigned int startPos = UINT_MAX, bool caseSensitive = true);

	WebData utf8(void);
	static WebString fromUTF8(const char* string);
	static WebString fromUTF8(const char* string, unsigned int len);
	static WebString format(const char* format, ...);

public:
	WebStringImpl* impl(void) const;
	explicit WebString(WebStringImpl* impl);

	UChar operator[](unsigned int index) const;
private:
	WebStringImpl* m_impl;
};

static inline bool operator ! (const WebString& str)
{
	return str.isNull();
}

static inline bool operator == (const WebString& a, const WebString& b)
{
	return a.equals(b);
}

static inline bool operator != (const WebString& a, const WebString& b)
{
	return !a.equals(b);
}

static inline WebString& operator += (WebString& a, const WebString& b)
{
	a.append(b);
	return a;
}

static inline WebString operator + (const WebString& a, const WebString& b)
{
    if (a.isEmpty())
        return b;
    if (b.isEmpty())
        return a;
    WebString c = a;
    c += b;
    return c;
}

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_STRING_H_*/

