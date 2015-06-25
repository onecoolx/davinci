
#ifndef TextCodecMg_h
#define TextCodecMg_h

#include "TextCodec.h"
#include "TextEncoding.h"

using namespace WTF;
namespace WebCore {
    class TextCodecPrivate;

    class TextCodecPlatform : public TextCodec {
    public:
        static void registerEncodingNames(EncodingNameRegistrar);
        static void registerCodecs(TextCodecRegistrar);

        TextCodecPlatform(const TextEncoding&);
        TextCodecPlatform(const char *name);
        virtual ~TextCodecPlatform();

        virtual String decode(const char*, size_t length, bool flush = false);
        virtual CString encode(const UChar*, size_t length, bool allowEntities = false);

    private:
        TextCodecPrivate* m_codec;
    };

} // namespace WebCore

#endif

