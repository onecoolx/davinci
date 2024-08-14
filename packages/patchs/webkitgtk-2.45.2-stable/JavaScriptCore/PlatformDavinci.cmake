set(JAVASCRIPTCORE_VERSION ${WEBKIT_VERSION})
set(JAVASCRIPTCORE_VERSION_MAJOR ${WEBKIT_VERSION_MAJOR})

if (ENABLE_REMOTE_INSPECTOR)
    if (APPLE)
        include(inspector/remote/Cocoa.cmake)
    else ()
        include(inspector/remote/Socket.cmake)
    endif ()
endif ()

# This overrides the default x64 value of 1GB for the memory pool size
#list(APPEND JavaScriptCore_PRIVATE_DEFINITIONS
#    FIXED_EXECUTABLE_MEMORY_POOL_SIZE_IN_MB=64
#)
if (NOT USE_SYSTEM_MALLOC)
    list(APPEND JavaScriptCore_LIBRARIES bmalloc)
endif ()
