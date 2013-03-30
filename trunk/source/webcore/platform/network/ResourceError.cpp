// -*- mode: c++; c-basic-offset: 4 -*-
/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "macross.h"
#include "ResourceError.h"

namespace WebCore {

#define ERR_NET_UNSUPPORTED  0

static int NetworkErrorCode[] = {
    ERR_NET_UNSUPPORTED,           /* CURLE_OK 0 */
    ERR_NET_UNSUPPORTED_PROTOCOL,  /* CURLE_UNSUPPORTED_PROTOCOL 1 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_FAILED_INIT 2 */
    ERR_NET_URL_ERROR,             /* CURLE_URL_MALFORMAT 3 */
    ERR_NET_UNSUPPORTED,           /* CURLE_URL_MALFORMAT_USER - NOT USED 4 */
    ERR_NET_PROXY_ERROR,           /* CURLE_COULDNT_RESOLVE_PROXY 5 */
    ERR_NET_DNS_ERROR,             /* CURLE_COULDNT_RESOLVE_HOST 6 */
    ERR_NET_CONNECT_FAILED,        /* CURLE_COULDNT_CONNECT 7 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WEIRD_SERVER_REPLY 8 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_ACCESS_DENIED 9 */
    ERR_NET_UNSUPPORTED,           /* CURLE_FTP_USER_PASSWORD_INCORRECT 10 - NOT USED */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WEIRD_PASS_REPLY 11 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WEIRD_USER_REPLY 12 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WEIRD_PASV_REPLY 13 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WEIRD_227_FORMAT 14 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_CANT_GET_HOST 15 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_CANT_RECONNECT 16 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_SET_BINARY 17 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_PARTIAL_FILE 18 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_RETR_FILE 19 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_WRITE_ERROR 20 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_QUOTE_ERROR 21 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_HTTP_RETURNED_ERROR 22 CURLOPT_FAILONERROR unsupport*/
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_WRITE_ERROR 23 */
    ERR_NET_UNSUPPORTED,           /* CURLE_MALFORMAT_USER 24 - NOT USED */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_STOR_FILE 25 - failed FTP upload */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_READ_ERROR 26 - could open/read from file */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_OUT_OF_MEMORY 27 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_OPERATION_TIMEOUTED 28 */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_SET_ASCII 29 - TYPE A failed */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_PORT_FAILED 30 - FTP PORT operation failed */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_USE_REST 31 - the REST command failed */
    ERR_NET_FTP_UNKNOWN_ERROR,     /* CURLE_FTP_COULDNT_GET_SIZE 32 - the SIZE command failed */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_HTTP_RANGE_ERROR 33 - RANGE "command" didn't work */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_HTTP_POST_ERROR 34 */
    ERR_NET_SSL_CONNECT_ERROR,     /* CURLE_SSL_CONNECT_ERROR 35 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_BAD_DOWNLOAD_RESUME 36 - couldn't resume download */
    ERR_NET_FILE_READ_ERROR,       /* CURLE_FILE_COULDNT_READ_FILE 37 */
    ERR_NET_UNSUPPORTED,           /* CURLE_LDAP_CANNOT_BIND 38 */
    ERR_NET_UNSUPPORTED,           /* CURLE_LDAP_SEARCH_FAILED 39 */
    ERR_NET_UNSUPPORTED,           /* CURLE_LIBRARY_NOT_FOUND 40 */
    ERR_NET_UNSUPPORTED,           /* CURLE_FUNCTION_NOT_FOUND 41 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_ABORTED_BY_CALLBACK 42 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_BAD_FUNCTION_ARGUMENT 43 */
    ERR_NET_UNSUPPORTED,           /* CURLE_BAD_CALLING_ORDER 44 - NOT USED */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_INTERFACE_FAILED 45 - CURLOPT_INTERFACE failed */
    ERR_NET_UNSUPPORTED,           /* CURLE_BAD_PASSWORD_ENTERED 46 - NOT USED */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_TOO_MANY_REDIRECTS 47 */
    ERR_NET_UNSUPPORTED,           /* CURLE_UNKNOWN_TELNET_OPTION 48 */
    ERR_NET_UNSUPPORTED,           /* CURLE_TELNET_OPTION_SYNTAX  49 - Malformed telnet option */
    ERR_NET_UNSUPPORTED,           /* CURLE_OBSOLETE 50 - NOT USED */
    ERR_NET_SSL_PEER_CERTIFICATE,  /* CURLE_SSL_PEER_CERTIFICATE 51 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_GOT_NOTHING 52 - when this is a specific error */
    ERR_NET_SSL_ENGINE_NOTFOUND,   /* CURLE_SSL_ENGINE_NOTFOUND 53 - SSL crypto engine not found */
    ERR_NET_SSL_ENGINE_SETFAILED,  /* CURLE_SSL_ENGINE_SETFAILED 54 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_SEND_ERROR 55 - failed sending network data */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_RECV_ERROR 56 - failure in receiving network data */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_SHARE_IN_USE 57 - share is in use */
    ERR_NET_SSL_CERTPROBLEM,       /* CURLE_SSL_CERTPROBLEM 58 */
    ERR_NET_SSL_CIPHER,            /* CURLE_SSL_CIPHER 59 - couldn't use specified cipher */
    ERR_NET_SSL_CACERT,            /* CURLE_SSL_CACERT 60 - problem with the CA cert (path?) */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_BAD_CONTENT_ENCODING 61 */
    ERR_NET_UNSUPPORTED,           /* CURLE_LDAP_INVALID_URL 62 - Invalid LDAP URL */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_FILESIZE_EXCEEDED 63 - Maximum file size exceeded */
    ERR_NET_SSL_FTP_ERROR,         /* CURLE_FTP_SSL_FAILED 64 - Requested FTP SSL level failed */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_SEND_FAIL_REWIND 65 */
    ERR_NET_SSL_ENGINE_INITFAILED, /* CURLE_SSL_ENGINE_INITFAILED 66 */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_LOGIN_DENIED 67 */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_NOTFOUND 68 - file not found on server */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_PERM 69 - permission problem on server */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_DISKFULL 70 - out of disk space on server */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_ILLEGAL 71 - Illegal TFTP operation */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_UNKNOWNID 72 - Unknown transfer ID */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_EXISTS 73 - File already exists */
    ERR_NET_UNSUPPORTED,           /* CURLE_TFTP_NOSUCHUSER 74 - No such user */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_CONV_FAILED 75 - conversion failed */
    ERR_NET_UNKNOWN_ERROR,         /* CURLE_CONV_REQD 76 - caller must register conversion */
    ERR_NET_SSL_CACERT_BADFILE,    /* CURLE_SSL_CACERT_BADFILE 77 */
    ERR_NET_UNSUPPORTED,           /* CURL_LAST never use! */
};                                 
                                   
void ResourceError::unpackPlatformError()
{
    if (!m_platformError && !m_type)
        return;
    if (m_type == HttpNetError)
        m_errorCode = m_platformError + ERR_NET_HTTP_BASE;
    else if (m_type == FtpNetError)
        m_errorCode = m_platformError + ERR_NET_FTP_BASE;
    else if (m_type == CurlNetError) {
        m_errorCode = NetworkErrorCode[m_platformError];
        if (m_errorCode == ERR_NET_UNSUPPORTED)
            return;
    }
    m_dataIsUpToDate = true;
}

} /* namespace WebCore */
