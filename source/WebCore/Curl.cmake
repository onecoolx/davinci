set(WEBCORE_IMP_DIR ${WORKSPACE_DIR}/source/WebCore)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_IMP_DIR}/platform/curl"
)

list(APPEND WebCore_SOURCES
    ${WEBCORE_IMP_DIR}/platform/curl/AuthenticationChallengeCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CertificateInfoCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CookieJarDB.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CookieStorageCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CookieUtil.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlContext.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlFormDataStream.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlMultipartHandle.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlProxySettings.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequest.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequestScheduler.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlSSLHandle.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlSSLVerifier.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlStream.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/CurlStreamScheduler.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/DNSResolveQueueCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/NetworkStorageSessionCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/OpenSSLHelper.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/ProtectionSpaceCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/PublicSuffixStoreCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceErrorCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceRequestCurl.cpp
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceResponseCurl.cpp
)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
    ${WEBCORE_IMP_DIR}/platform/curl/AuthenticationChallenge.h
    ${WEBCORE_IMP_DIR}/platform/curl/CertificateInfo.h
    ${WEBCORE_IMP_DIR}/platform/curl/CookieJarDB.h
    ${WEBCORE_IMP_DIR}/platform/curl/CookieUtil.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlContext.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlFormDataStream.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlMultipartHandle.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlMultipartHandleClient.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlProxySettings.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequest.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequestClient.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequestScheduler.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlRequestSchedulerClient.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlResponse.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlSSLHandle.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlSSLVerifier.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlStream.h
    ${WEBCORE_IMP_DIR}/platform/curl/CurlStreamScheduler.h
    ${WEBCORE_IMP_DIR}/platform/curl/DNSResolveQueueCurl.h
    ${WEBCORE_IMP_DIR}/platform/curl/OpenSSLHelper.h
    ${WEBCORE_IMP_DIR}/platform/curl/ProtectionSpaceCurl.h
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceError.h
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceRequest.h
    ${WEBCORE_IMP_DIR}/platform/curl/ResourceResponse.h
)

list(APPEND WebCore_LIBRARIES
    CURL::libcurl
)
