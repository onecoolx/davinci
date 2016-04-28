/*
 * WebUrl.h: Url implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_URL_H_
#define _DAVINCI_URL_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

class WebUrlImpl;

class EXPORT_API WebUrl : public WebObject
{
public:
    WebUrl();
    WebUrl(const char* url);
    WebUrl(const UChar* url, unsigned int len);
    WebUrl(const WebString& url);
    WebUrl(const WebUrl& other);
    WebUrl& operator=(const WebUrl& other);

    virtual ~WebUrl();
public:
    bool isEmpty(void) const;
    bool isValid(void) const;
    bool isLocalFile(void) const;

    WebString protocol(void) const;
    WebString host(void) const;
    WebString path(void) const;
    WebString query(void) const;
    WebString userName(void) const;
    WebString passWord(void) const;
    unsigned int port(void) const;
    WebString fragment(void) const;

    WebString toString(void) const;
public:
    WebUrlImpl* impl(void) const;	
private:
    WebUrlImpl* m_impl;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_URL_H_*/
