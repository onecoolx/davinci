/*
 * WebData.cpp: WebData implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"

#include "WebCommon.h"
#include "WebObject.h"
#include "WebData.h"

#include "SharedBuffer.h"

namespace davinci {

class WebDataImpl : public WebCore::SharedBuffer 
{
};

WebData::WebData()
	: m_impl(0)
{
    RefPtr<WebCore::SharedBuffer> buffer = WebCore::SharedBuffer::create();
    m_impl = static_cast<WebDataImpl*>(buffer.get());
    m_impl->ref();
}

WebData::WebData(const Byte* data, unsigned int size)
	: m_impl(0)
{
    RefPtr<WebCore::SharedBuffer> buffer = WebCore::SharedBuffer::create(data, size);
    m_impl = static_cast<WebDataImpl*>(buffer.get());
    m_impl->ref();
}

WebData::WebData(const WebData& o)
{
    if (o.m_impl)
        o.m_impl->ref();
	m_impl = o.m_impl;
}

WebData::~WebData()
{
    if (m_impl)
        m_impl->deref();
}

WebData& WebData::operator=(const WebData& o)
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

bool WebData::isEmpty(void) const
{
	return const_cast<WebDataImpl*>(m_impl)->isEmpty();
}

size_t WebData::size(void) const
{
	return const_cast<WebDataImpl*>(m_impl)->size();
}

const Byte* WebData::data(void) const
{
	return (const Byte*)(m_impl->data());
}

const char* WebData::toString(void) const
{
	if (data()[size()] == 0) { // null terminal
		return (const char*)data();
	} else {
		m_impl->append("\0", 1);
		return (const char*)data();
	}
}

Byte WebData::operator[](unsigned int index) const
{
	if (index >= size())
		return 0;
	return m_impl->data()[index];
}

}
