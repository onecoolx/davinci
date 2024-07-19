# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(XSLT_NAME "libxslt")
set(XSLT_VERSION "v1.1.42")
set(XSLT_PACKAGE "${PROJECT_ROOT}/packages/${XSLT_NAME}-${XSLT_VERSION}.tar.gz")
set(XSLT_HASH "b950e8c873069eb570dbc5828eed5a522fc2486edc0cc1dc01d3a360b63a8a62")

ExternalProject_Add(
  ${XSLT_NAME}
  PREFIX "${PROJECT_OUT}/${XSLT_NAME}"
  URL "${XSLT_PACKAGE}"
  URL_HASH SHA256=${XSLT_HASH}
  BUILD_IN_SOURCE
  CMAKE_ARGS -DLIBXSLT_WITH_PYTHON=OFF -DLIBXSLT_WITH_PROGRAMS=OFF -DLIBXSLT_WITH_TESTS=OFF -DLIBXSLT_WITH_XSLT_DEBUG=OFF -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
include_directories(${PROJECT_OUT}/include)
link_directories(${PROJECT_OUT}/lib)

add_dependencies(${XSLT_NAME} ${XML2_NAME})
