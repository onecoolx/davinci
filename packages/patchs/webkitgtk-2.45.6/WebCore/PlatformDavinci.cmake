include(platform/Adwaita.cmake)
#include(platform/GCrypt.cmake)
#include(platform/GStreamer.cmake)
include(platform/ImageDecoders.cmake)
include(platform/TextureMapper.cmake)
include(platform/Skia.cmake)

include(${WORKSPACE_DIR}/source/WebCore/Curl.cmake)

list(APPEND WebCore_UNIFIED_SOURCE_LIST_FILES
    "SourcesDavinci.txt"
)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/crypto/openssl"
    "${WEBCORE_DIR}/platform/generic"
    "${WEBCORE_DIR}/platform/graphics/gstreamer"
    "${WEBCORE_DIR}/platform/graphics/opengl"
    "${WEBCORE_DIR}/platform/graphics/opentype"
    "${WEBCORE_DIR}/platform/mediacapabilities"
    "${WEBCORE_DIR}/platform/mediastream/gstreamer"
    "${WEBCORE_DIR}/platform/mock/mediasource"
)

list(APPEND WebCore_PRIVATE_INCLUDE_DIRECTORIES
    "${WORKSPACE_DIR}/source/WTF"
    "${WORKSPACE_DIR}/source/WebCore"
    "${WORKSPACE_DIR}/source/WebCore/platform/graphics/egl"
    "${WORKSPACE_DIR}/source/WebCore/accessibility"
    "${WORKSPACE_DIR}/source/WebCore/accessibility/davinci"
    "${WORKSPACE_DIR}/source/WebCore/accessibility/isolatedtree"
)

list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
    platform/graphics/egl/PlatformDisplaySurfaceless.h
)

set(CSS_VALUE_PLATFORM_DEFINES "HAVE_OS_DARK_MODE_SUPPORT=1")

list(APPEND WebCore_LIBRARIES
)

list(APPEND WebCore_SYSTEM_INCLUDE_DIRECTORIES
)

if (ENABLE_GAMEPAD)
    list(APPEND WebCore_PRIVATE_FRAMEWORK_HEADERS
        platform/gamepad/manette/ManetteGamepadProvider.h
    )
    list(APPEND WebCore_LIBRARIES
        Manette::Manette
    )
endif ()

if (ENABLE_SPEECH_SYNTHESIS)
    list(APPEND WebCore_SYSTEM_INCLUDE_DIRECTORIES
        ${Flite_INCLUDE_DIRS}
    )
    list(APPEND WebCore_LIBRARIES
        ${Flite_LIBRARIES}
    )
endif ()

include_directories(SYSTEM
    ${WebCore_SYSTEM_INCLUDE_DIRECTORIES}
)

if (ENABLE_SMOOTH_SCROLLING)
    list(APPEND WebCore_SOURCES
        platform/ScrollAnimationSmooth.cpp
    )
endif ()

