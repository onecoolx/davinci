# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(CURL_NAME "curl")
set(CURL_VERSION "8.8.0")
set(CURL_PACKAGE "${PROJECT_ROOT}/packages/${CURL_NAME}-${CURL_VERSION}.tar.gz")
set(CURL_HASH "77c0e1cd35ab5b45b659645a93b46d660224d0024f1185e8a95cdb27ae3d787d")

ExternalProject_Add(
  ${CURL_NAME}
  PREFIX "${PROJECT_OUT}/${CURL_NAME}"
  URL "${CURL_PACKAGE}"
  URL_HASH SHA256=${CURL_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBUILD_CURL_EXE=OFF -DCURL_USE_MBEDTLS=ON -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
include_directories(${PROJECT_OUT}/include)
link_directories(${PROJECT_OUT}/lib)

add_dependencies(${CURL_NAME} ${ZLIB_NAME} ${MTLS_NAME})
