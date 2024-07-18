# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(PNG_NAME "libpng")
set(PNG_VERSION "1.6.43")
set(PNG_PACKAGE "${PROJECT_ROOT}/packages/${PNG_NAME}-${PNG_VERSION}.tar.gz")
set(PNG_HASH "e804e465d4b109b5ad285a8fb71f0dd3f74f0068f91ce3cdfde618180c174925")

ExternalProject_Add(
  ${PNG_NAME}
  PREFIX "${PROJECT_OUT}/${PNG_NAME}"
  URL "${PNG_PACKAGE}"
  URL_HASH SHA256=${PNG_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DPNG_TESTS=OFF -DPNG_TOOLS=OFF -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
