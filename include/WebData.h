/*
 * WebData.h: Raw data container implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_RAWDATA_H_
#define _DAVINCI_RAWDATA_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

class WebDataImpl;

class EXPORT_API WebData : public WebObject
{
public:
    WebData();
    WebData(const Byte* data, unsigned int size);
    WebData(const WebData& other);
    WebData& operator=(const WebData& other);
    virtual ~WebData();
public:
    size_t size(void) const;
    const Byte* data(void) const;
    const char* toString(void) const;

    bool isEmpty(void) const;

    Byte operator[](unsigned int index) const;
private:
    WebDataImpl* m_impl;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_RAWDATA_H_*/

