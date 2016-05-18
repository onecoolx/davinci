/*
 * WebEncoding.h: Text Encoding define.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_ENCODEING_H_
#define _DAVINCI_ENCODEING_H_

namespace davinci {
/**
 * \defgroup content TextEncoding
 * @{
 */

/** 
 * \brief Encoding name which the webview supported.
 */
typedef enum {
    /** 
     * Autodetect character encoding.
     */
    CHARSET_AUTO_DETECT = -1,
    /** 
     * Western (ISO-8859-1).
     */
    CHARSET_ISO8859_1,
    /** 
     * Central European (ISO-8859-2).
     */
    CHARSET_ISO8859_2, 
    /** 
     * South European (ISO-8859-3).
     */
    CHARSET_ISO8859_3,
    /** 
     * Baltic (ISO-8859-4).
     */
    CHARSET_ISO8859_4,
    /** 
     * Cyrillic (ISO-8859-5).
     */
    CHARSET_ISO8859_5,
    /** 
     * Arabic (ISO-8859-6).
     */
    CHARSET_ISO8859_6,
    /** 
     * Greek (ISO-8859-7).
     */
    CHARSET_ISO8859_7,
    /** 
     * Hebrew Visual (ISO-8859-8).
     */
    CHARSET_ISO8859_8,
    /** 
     * Turkish (ISO-8859-9).
     */
    CHARSET_ISO8859_9,
    /** 
     * Nordic (ISO-8859-10).
     */
    CHARSET_ISO8859_10,
    /** 
     * Thai (ISO-8859-11).
     */
    CHARSET_ISO8859_11,
    /** 
     * Baltic (ISO-8859-13).
     */
    CHARSET_ISO8859_13,
    /** 
     * Celtic (ISO-8859-14).
     */
    CHARSET_ISO8859_14,
    /** 
     * Western (ISO-8859-15).
     */
    CHARSET_ISO8859_15,
    /** 
     * Romanian (ISO-8859-16).
     */
    CHARSET_ISO8859_16,
    /** 
     * Chinese Simplified (GB2312).
     */
    CHARSET_GB2312,
    /** 
     * Chinese Simplified (GBK).
     */
    CHARSET_GBK,
    /** 
     * Chinese Traditional (Big5).
     */
    CHARSET_BIG5,
    /** 
     * Korean (EUC-KR).
     */
    CHARSET_EUCKR,
    /** 
     * Japanese (EUC-JP).
     */
    CHARSET_EUCJP,
    /** 
     * Japanese (Shift-JIS).
     */
    CHARSET_SHIFTJIS,
    /** 
     * Unicode (UTF-8).
     */
    CHARSET_UTF8,
} WebEncodingType;

/** @} end of content*/

} /* namespace davinci */

#endif /*_DAVINCI_ENCODEING_H_*/
