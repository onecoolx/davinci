# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(ZLIB_NAME "zlib")
set(ZLIB_VERSION "1.3.1")
set(ZLIB_PACKAGE "${PROJECT_ROOT}/packages/${ZLIB_NAME}-${ZLIB_VERSION}.tar.gz")
set(ZLIB_HASH "9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23")

ExternalProject_Add(
  ${ZLIB_NAME}
  PREFIX "${PROJECT_OUT}/${ZLIB_NAME}"
  URL "${ZLIB_PACKAGE}"
  URL_HASH SHA256=${ZLIB_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DZLIB_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
