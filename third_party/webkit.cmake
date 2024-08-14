# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(WEBKIT_NAME "webkitgtk")
set(WEBKIT_VERSION "2.45.2-stable")
set(WEBKIT_PACKAGE "${PROJECT_ROOT}/packages/${WEBKIT_NAME}-${WEBKIT_VERSION}.tar")
set(WEBKIT_HASH "523f42c8ff24832add17631f6eaafe8f9303afe316ef1a7e1844b952a7f7521b")

set(WEBKIT_OPTIONS
  -DWORKSPACE_DIR=${PROJECT_ROOT}
  -DWORKSPACE_OUT=${PROJECT_OUT}
  -DENABLE_API_TESTS=FALSE
  -DENABLE_LAYOUT_TESTS=FALSE
  -DDEVELOPER_MODE=FALSE
  -DENABLE_MINIBROWSER=FALSE
  -DUSE_APPLE_ICU=FALSE
  -DPORT=Davinci
)

ExternalProject_Add(
  ${WEBKIT_NAME}
  PREFIX "${PROJECT_OUT}/${WEBKIT_NAME}"
  URL "${WEBKIT_PACKAGE}"
  URL_HASH SHA256=${WEBKIT_HASH}
  PATCH_COMMAND
     ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${WEBKIT_NAME}-${WEBKIT_VERSION}/WebKitCommon.cmake"
    "${PROJECT_OUT}/${WEBKIT_NAME}/src/${WEBKIT_NAME}/Source/cmake/WebKitCommon.cmake"
  && ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${WEBKIT_NAME}-${WEBKIT_VERSION}/bmalloc/PlatformDavinci.cmake"
    "${PROJECT_OUT}/${WEBKIT_NAME}/src/${WEBKIT_NAME}/Source/bmalloc/PlatformDavinci.cmake"
  && ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${WEBKIT_NAME}-${WEBKIT_VERSION}/WTF/PlatformDavinci.cmake"
    "${PROJECT_OUT}/${WEBKIT_NAME}/src/${WEBKIT_NAME}/Source/WTF/wtf/PlatformDavinci.cmake"
  && ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${WEBKIT_NAME}-${WEBKIT_VERSION}/JavaScriptCore/PlatformDavinci.cmake"
    "${PROJECT_OUT}/${WEBKIT_NAME}/src/${WEBKIT_NAME}/Source/JavaScriptCore/PlatformDavinci.cmake"
  && ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${WEBKIT_NAME}-${WEBKIT_VERSION}/OptionsDavinci.cmake"
    "${PROJECT_OUT}/${WEBKIT_NAME}/src/${WEBKIT_NAME}/Source/cmake/OptionsDavinci.cmake"
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT} -j 4
  ${WEBKIT_OPTIONS}
)

include_directories(${PROJECT_OUT}/include)
link_directories(${PROJECT_OUT}/lib)

add_dependencies(
    ${WEBKIT_NAME}
    ${HARFBUZZ_NAME}
    ${ICU_NAME}
    ${FREETYPE_NAME}
    ${XSLT_NAME}
    ${XML2_NAME}
    ${UV_NAME}
    ${CURL_NAME}
    ${MTLS_NAME}
    ${SQLITE_NAME}
    ${JPEG_NAME}
    ${PNG_NAME}
    ${ZLIB_NAME}
)

