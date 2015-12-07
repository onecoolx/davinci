
#ifndef ImageBufferDataDavinci_h
#define ImageBufferDataDavinci_h

#include "IntSize.h"

namespace WebCore {

class IntSize;

class ImageBufferData
{
public:
    void getImageData(GraphicsContext*, const IntRect&, const IntRect&, unsigned char* result, bool unmultiply) const;
    void draw(GraphicsContext* thisContext, GraphicsContext* otherContext, ColorSpace styleColorSpace, const FloatRect& destRect, const FloatRect& srcRect, CompositeOperator, bool useLowQualityScale) const;
    ImageBufferData(const IntSize&);

    IntSize m_size;

};

} // namespace WebCore

#endif
