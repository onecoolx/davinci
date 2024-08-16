# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(WEBP_NAME "libwebp")
set(WEBP_VERSION "1.4.0")
set(WEBP_PACKAGE "${PROJECT_ROOT}/packages/${WEBP_NAME}-${WEBP_VERSION}.tar.gz")
set(WEBP_HASH "12af50c45530f0a292d39a88d952637e43fb2d4ab1883c44ae729840f7273381")

ExternalProject_Add(
  ${WEBP_NAME}
  PREFIX "${PROJECT_OUT}/${WEBP_NAME}"
  URL "${WEBP_PACKAGE}"
  URL_HASH SHA256=${WEBP_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBUILD_SHARED_LIBS=TRUE -DWEBP_ENABLE_SIMD_DEFAULT=ON -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
include_directories(${PROJECT_OUT}/include)
link_directories(${PROJECT_OUT}/lib)

add_dependencies(
    ${WEBP_NAME}
    ${JPEG_NAME}
    ${PNG_NAME}
    ${ZLIB_NAME}
)

