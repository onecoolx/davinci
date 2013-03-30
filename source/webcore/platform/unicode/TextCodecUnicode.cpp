
#include <stdlib.h>
#include <string.h>

#include "charset.h"
#include "TextCodecUnicode.h"

class UTextCodec
{
public:
	UTextCodec(const char* name)
		: m_ops(create_charset_ops(name))
	{
	}

	~UTextCodec()
	{
		destory_charset_ops(m_ops);
	}

	const char* charset() { return m_ops ? m_ops->charset : 0;}

	charset_ops * ops() { return m_ops; }
private:
    charset_ops * m_ops;
};

UTextCodec * CreateCodec(const char* name)
{
	return new UTextCodec(name);
}

void DestoryCodec(UTextCodec* codec)
{
	delete codec;
}

const char * GetCodecName(UTextCodec* codec)
{
	return codec->charset();
}

int UTextDecode(UTextCodec* codec, UChar16* dest, int n, const unsigned char* mstr, int mstr_len, int* conved_mstr_len)
{
	if (!codec || !codec->ops() || !dest || n <=0 || !mstr || mstr_len<=0)
		return -1;

    int count = 0;
	int left = mstr_len;

	while (left > 0) {
		int len_cur_char = codec->ops()->len_first_char(mstr, left);
		if (len_cur_char <= 0){ //first char can not be decode
			if ((*mstr) && (*mstr <= 0x7F)) { //is ascii char except NULL
				dest[count] = *((const unsigned char*)mstr);
				count++;
			}
			mstr++; left--;
			continue;
		}

		UChar16 uc = codec->ops()->conv_to_uchar(mstr, len_cur_char);
		dest[count] = uc;

		count++;

		if (count == n)
			break;

		mstr += len_cur_char;
		left -= len_cur_char;
	}

	if (dest && count < n) {
		dest[count] = 0;
	}

    if (conved_mstr_len)
        *conved_mstr_len = mstr_len - left;
    return count;
}

int UTextEncode(UTextCodec* codec, unsigned char* dest, int n, const UChar16 *wcs, int wcs_len, int* conved_wcs_len)
{
	if (!codec || !codec->ops() || !dest || n <=0 || !wcs || wcs_len<=0)
		return -1;

    int wc_count = 0, count = 0;
    unsigned char mchar [16] = {0};
	UChar16 ucode = 0;

	while (wc_count < wcs_len) {
		ucode = *wcs;
        int len_cur_char = codec->ops()->conv_from_uchar(ucode, mchar);
		if (!len_cur_char) {
			*dest = (unsigned char)ucode;
			wcs++; wc_count++; dest++; count++;
			continue;
		}

		if (count + len_cur_char > n)
			break;
		
		if (dest) {
			memcpy(dest, mchar, len_cur_char);
			dest += len_cur_char;
		}
		
		count += len_cur_char;
		wc_count++;
		wcs++;
	}

	if (dest && count < n)
		*dest = '\0';

    if (conved_wcs_len)
        *conved_wcs_len = wc_count;

    return count;
}

