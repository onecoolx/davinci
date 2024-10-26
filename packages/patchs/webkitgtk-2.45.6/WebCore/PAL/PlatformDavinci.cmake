list(APPEND PAL_PUBLIC_HEADERS
    crypto/gcrypt/Handle.h
    crypto/gcrypt/Initialization.h
    crypto/gcrypt/Utilities.h
    crypto/tasn1/Utilities.h
)

list(APPEND PAL_SOURCES
    crypto/gcrypt/CryptoDigestGCrypt.cpp

    crypto/tasn1/Utilities.cpp

    system/ClockGeneric.cpp

    text/KillRing.cpp

    unix/LoggingUnix.cpp
)

list(APPEND PAL_PRIVATE_INCLUDE_DIRECTORIES
    "${WORKSPACE_DIR}/source/WTF"
    "${WORKSPACE_DIR}/source/WebCore"
)
