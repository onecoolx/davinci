set(JAVASCRIPTCORE_VERSION ${WEBKIT_VERSION})
set(JAVASCRIPTCORE_VERSION_MAJOR ${WEBKIT_VERSION_MAJOR})

if (ENABLE_REMOTE_INSPECTOR)
    if (APPLE)
        include(inspector/remote/Cocoa.cmake)
    else ()
        include(inspector/remote/Socket.cmake)
    endif ()
endif ()

list(APPEND JavaScriptCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WORKSPACE_DIR}/source/WTF"
    "${WORKSPACE_DIR}/source/WebCore"
)

if (USE_LIBBACKTRACE)
    list(APPEND WTF_LIBRARIES
        LIBBACKTRACE::LIBBACKTRACE
    )
endif ()

if (NOT USE_SYSTEM_MALLOC)
    list(APPEND JavaScriptCore_LIBRARIES bmalloc)
endif ()
