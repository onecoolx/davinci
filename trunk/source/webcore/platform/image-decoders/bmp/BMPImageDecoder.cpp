 
#include "BMPImageDecoder.h"

#ifdef BMP_SUPPORT

namespace WebCore
{

BMPImageDecoder::BMPImageDecoder()
	:m_reader(0)
{
    
}

BMPImageDecoder::~BMPImageDecoder()
{
}

void BMPImageDecoder::setData(const Vector<char>& data, bool allDataReceived)
{
}

void BMPImageDecoder::decode(bool sizeOnly)
{
}

bool BMPImageDecoder::isSizeAvailable()
{
	return false;
}
 
PixelsBuffer* BMPImageDecoder::frameBufferAtIndex(size_t index)
{
	return 0;
}

void BMPImageDecoder::addLineData (void * bufferheader, int index)
{

}

void BMPImageDecoder::setSize (const IntSize & size)
{
}

}

#endif /* BMP_SUPPORT */

