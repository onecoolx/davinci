# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(UV_NAME "libuv")
set(UV_VERSION "v1.48.0")
set(UV_PACKAGE "${PROJECT_ROOT}/packages/${UV_NAME}-${UV_VERSION}.tar.gz")
set(UV_HASH "7f1db8ac368d89d1baf163bac1ea5fe5120697a73910c8ae6b2fffb3551d59fb")

ExternalProject_Add(
  ${UV_NAME}
  PREFIX "${PROJECT_OUT}/${UV_NAME}"
  URL "${UV_PACKAGE}"
  URL_HASH SHA256=${UV_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DLIBUV_BUILD_TESTS=OFF -DLIBUV_BUILD_BENCH=OFF -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
