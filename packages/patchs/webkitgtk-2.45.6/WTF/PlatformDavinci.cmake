WEBKIT_APPEND_GLOBAL_COMPILER_FLAGS(-DWTF_PLATFORM_DAVINCI=1)

list(APPEND WTF_PUBLIC_HEADERS
    linux/RealTimeThreads.h
    unix/UnixFileDescriptor.h
)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND WTF_PUBLIC_HEADERS
        linux/ProcessMemoryFootprint.h
        linux/CurrentProcessMemoryStatus.h
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    list(APPEND WTF_PUBLIC_HEADERS
        spi/darwin/OSVariantSPI.h
        spi/darwin/ProcessMemoryFootprint.h
    )
endif ()

list(APPEND WTF_SOURCES
    generic/MainThreadGeneric.cpp
    generic/RunLoopGeneric.cpp
    generic/WorkQueueGeneric.cpp

    posix/CPUTimePOSIX.cpp
    posix/FileSystemPOSIX.cpp
    posix/OSAllocatorPOSIX.cpp
    posix/ThreadingPOSIX.cpp

    text/unix/TextBreakIteratorInternalICUUnix.cpp

    unix/LoggingUnix.cpp
    unix/MemoryPressureHandlerUnix.cpp
    unix/UniStdExtrasUnix.cpp
)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND WTF_SOURCES
        linux/CurrentProcessMemoryStatus.cpp
        linux/MemoryFootprintLinux.cpp
        linux/RealTimeThreads.cpp

        unix/MemoryPressureHandlerUnix.cpp
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
    list(APPEND WTF_SOURCES
        generic/MemoryFootprintGeneric.cpp

        unix/MemoryPressureHandlerUnix.cpp
    )
else ()
    list(APPEND WTF_SOURCES
        generic/MemoryFootprintGeneric.cpp
        generic/MemoryPressureHandlerGeneric.cpp
    )
endif ()

list(APPEND WTF_PRIVATE_INCLUDE_DIRECTORIES
    "${WORKSPACE_DIR}/source/WTF"
)

list(APPEND WTF_SOURCES
    ${WORKSPACE_DIR}/source/WTF/wtf/LanguageDavinci.cpp
)

list(APPEND WTF_LIBRARIES
    ${KERNEL_LIBRARY}
    Threads::Threads
)

install(TARGETS WTF LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
