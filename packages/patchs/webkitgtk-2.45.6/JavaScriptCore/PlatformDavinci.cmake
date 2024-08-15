set(JAVASCRIPTCORE_VERSION ${WEBKIT_VERSION})
set(JAVASCRIPTCORE_VERSION_MAJOR ${WEBKIT_VERSION_MAJOR})

if (ENABLE_REMOTE_INSPECTOR)
    if (APPLE)
        include(inspector/remote/Cocoa.cmake)
    else ()
        include(inspector/remote/Socket.cmake)
    endif ()
endif ()

if (USE_LIBBACKTRACE)
    list(APPEND WTF_LIBRARIES
        LIBBACKTRACE::LIBBACKTRACE
    )
endif ()

if (NOT USE_SYSTEM_MALLOC)
    list(APPEND JavaScriptCore_LIBRARIES bmalloc)
endif ()
