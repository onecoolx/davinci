
#ifndef _PIXELARRAY_H_
#define _PIXELARRAY_H_
#include "config.h"
#include <string.h>
#include <wtf/Vector.h>

namespace WebCore {

extern int pixelPerBytes(void);

class PixelArray
{
public:
    PixelArray()
        :m_bpp(pixelPerBytes())
    {
    }

    ~PixelArray()
    {
    }

    void resize(size_t size)
    {
        m_data.resize(size * m_bpp);
    }

    void init(unsigned initPixel)
    {
		//FIXME: need memset2 or memset4 for initPixel fill.
		memset(m_data.data(), 0x0, m_data.size());
    }

    void setPixel(unsigned index, unsigned idata)
    {
		register unsigned char* data = (unsigned char*)(&idata);
		register unsigned char* dst = m_data.data()+index*m_bpp;
		for (unsigned i = 0; i < m_bpp; i++) {
			*(unsigned char*)((int)dst+i) = *(unsigned char*)((int)data+i);	
		}
    }

    unsigned bytePixel(void) 
    {
        return m_bpp;
    }

    unsigned char * data(void) 
    {
        return m_data.data();
    }
private:
    unsigned m_bpp;
    Vector<unsigned char> m_data; // The pixels data.
};

}
#endif /*_PIXELARRAY_H_*/

