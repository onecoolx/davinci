
#ifndef ImageBufferDataDavinci_h
#define ImageBufferDataDavinci_h

#include "IntSize.h"

namespace WebCore {

class IntSize;

class ImageBufferData
{
public:
    ImageBufferData(const IntSize&);

    IntSize m_size;

};

} // namespace WebCore

#endif
