/*
** TextCodecPS.cpp: TextCodec implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"

#include "Shared.h"
#include "TextCodecPlatform.h"
#include "CString.h"
#include "PlatformString.h"
#include <wtf/HashSet.h>
#include "TextCodecUnicode.h" 

using std::auto_ptr;
namespace WebCore {

const size_t BufferSize = 16384;

class TextCodecPrivate : public Noncopyable
{
public:
    TextCodecPrivate(const TextEncoding& encoding)
        :m_codec(CreateCodec(encoding.name()))
    {
    }

    virtual ~TextCodecPrivate()
    {
		DestoryCodec(m_codec);
    }

    UTextCodec*  getImpl(void) const {return m_codec;}
    const char * getEncoding(void)const {return GetCodecName(m_codec);}
private:
    UTextCodec* m_codec;
};

TextCodecPlatform::TextCodecPlatform(const TextEncoding& encoding)
{
    m_codec = new TextCodecPrivate(encoding);
}

TextCodecPlatform::TextCodecPlatform(const char *name)
{
    m_codec = new TextCodecPrivate(TextEncoding(name));
}

TextCodecPlatform::~TextCodecPlatform()
{
    delete m_codec;
}

void TextCodecPlatform::registerEncodingNames(EncodingNameRegistrar registrar)
{
#if ENABLE(HEBREW_SUPPORT)
    registrar("ISO8859-8", "ISO8859-8");
    registrar("visual", "ISO8859-8");
#endif /* ISO8859-8 */ 

#if ENABLE(GBK_SUPPORT)
    registrar("EUC-CN", "GBK");
    registrar("xeuccn", "GBK");
    registrar("xgbk", "GBK");
    registrar("csgb231280", "GBK");
    registrar("cngb", "GBK");
    registrar("GB2312-0", "GBK");
    registrar("GB2312", "GBK");
    registrar("GB_2312-80", "GBK");
    registrar("GBK", "GBK");
#elif ENABLE(GB2312_SUPPORT)
    registrar("EUC-CN", "GB2312-0");
    registrar("csgb231280", "GB2312-0");
    registrar("cngb", "GB2312-0");
    registrar("GB2312-0", "GB2312-0");
    registrar("GB2312", "GB2312-0");
    registrar("GB_2312-80", "GB2312-0");
    registrar("GBK", "GB2312");
    registrar("xgbk", "GB2312");
#endif /* GB2312 */

#if ENABLE(BIG5_SUPPORT)
    registrar("BIG5", "BIG5");
    registrar("cnbig5", "BIG5");
    registrar("xxbig5", "BIG5");
#endif /* BIG5 */

#if ENABLE(EUCKR_SUPPORT)
    registrar("EUC-KR", "EUC-KR");
    registrar("KSC5601-0", "EUC-KR");
    registrar("KSC_5601", "EUC-KR");
    registrar("cp1363", "EUC-KR");
#endif /* EUC-KR */

#if ENABLE(EUCJP_SUPPORT)
    registrar("EUC-JP", "EUC-JP");
    registrar("xeuc", "EUC-JP");
    registrar("JISX0208-0", "EUC-JP");
#endif /* EUC-JP */

#if ENABLE(SHIFTJIS_SUPPORT)
    registrar("SHIFT-JIS", "SHIFT-JIS");
    registrar("cp932", "SHIFT-JIS");
    registrar("JISX0208-1", "SHIFT-JIS");
#endif /* SHIFT-JIS */

    registrar("UTF-8", "UTF-8");
    registrar("utf-8", "UTF-8");
    registrar("unicode11utf8", "UTF-8");
    registrar("unicode20utf8", "UTF-8");
    registrar("xunicode20utf8", "UTF-8");
}

static auto_ptr<TextCodec> newTextCodecPlatform(const TextEncoding& encoding, const void*)
{
    return auto_ptr<TextCodec>(new TextCodecPlatform(encoding));
}

void TextCodecPlatform::registerCodecs(TextCodecRegistrar registrar)
{
#if ENABLE(GBK_SUPPORT)
    registrar("GBK", newTextCodecPlatform, 0);
#elif ENABLE(GB2312_SUPPORT)
    registrar("GB2312-0", newTextCodecPlatform, 0);
#endif /* GB2312 */

#if ENABLE(BIG5_SUPPORT)
    registrar("BIG5", newTextCodecPlatform, 0);
#endif /* BIG5 */

#if ENABLE(EUCKR_SUPPORT)
    registrar("EUC-KR", newTextCodecPlatform, 0);
#endif /* EUC-KR */

#if ENABLE(EUCJP_SUPPORT)
    registrar("EUC-JP", newTextCodecPlatform, 0);
#endif /* EUC-JP */

#if ENABLE(SHIFTJIS_SUPPORT)
    registrar("SHIFT-JIS", newTextCodecPlatform, 0);
#endif /* SHIFT-JIS */

    registrar("UTF-8", newTextCodecPlatform, 0);

}

String TextCodecPlatform::decode(const char* bytes, size_t length, bool flush)
{
    Vector<UChar> result;
    int len, blen;
    
    unsigned char buffer[BufferSize];
    const unsigned char* source = reinterpret_cast<const unsigned char*>(bytes);
    size_t offset = 0;

    do {
        memset(buffer, 0 , BufferSize);
        source = reinterpret_cast<const unsigned char*>(bytes) + offset;
        size_t tlen = ((length - offset) > (BufferSize>>2)) ? (BufferSize>>2) : (length - offset);
        len = UTextDecode(m_codec->getImpl(), (unsigned short*)buffer, BufferSize>>1, source, tlen, &blen);
        if (len < 0)
            break;
        appendOmittingBOM(result, reinterpret_cast<const UChar*>(buffer), len);
		offset += blen ? blen : tlen; //FIXME: for NULL string.
    } while (offset < length);

    return String::adopt(result);
}


CString TextCodecPlatform::encode(const UChar* characters, size_t length, bool allowEntities)
{
    Vector<char> result;
    int len, blen;
    unsigned char buffer[BufferSize];

    size_t offset = 0;
    size_t size = 0;
    const UChar* source = characters;

    do {
        memset(buffer, 0 , BufferSize);
        source = characters + offset;
        size_t tlen = ((length - offset) > (BufferSize>>2)) ? (BufferSize>>2) : (length - offset);
        len = UTextEncode(m_codec->getImpl(), buffer, BufferSize>>2, source, tlen, &blen);
        if (len < 0)
             break;

        result.resize(size + len);
        memcpy(result.data() + size, buffer, len);
		size += len;
		offset += blen ? blen : tlen;//FIXME: for NULL string.
    } while (offset < length);

    return CString(result.data(), result.size());
}

}
