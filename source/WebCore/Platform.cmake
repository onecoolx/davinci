set(WEBCORE_IMP_DIR ${WORKSPACE_DIR}/source/WebCore)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_IMP_DIR}/platform"
    "${WEBCORE_IMP_DIR}/platform/graphics"
    "${WEBCORE_IMP_DIR}/platform/graphics/egl"
    "${WEBCORE_IMP_DIR}/platform/accessibility"
)

list(APPEND WebCore_SOURCES
    ${WEBCORE_IMP_DIR}/platform/DragData.cpp
    ${WEBCORE_IMP_DIR}/platform/Pasteboard.cpp
    ${WEBCORE_IMP_DIR}/platform/Screen.cpp
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLFence.cpp
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLContext.cpp
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLContextWrapper.cpp
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/PlatformDisplaySurfaceless.cpp
)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLContext.h
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLContextWrapper.h
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/GLFence.h
    ${WEBCORE_IMP_DIR}/platform/graphics/egl/PlatformDisplaySurfaceless.h
)

