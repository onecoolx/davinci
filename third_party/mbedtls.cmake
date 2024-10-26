# HTML5 runtime
# 
# Copyright (C) 2024 Zhang Ji Peng
# Contact: onecoolx@gmail.com

include(ExternalProject)

set(MTLS_NAME "mbedtls")
set(MTLS_VERSION "3.6.0")
set(MTLS_PACKAGE "${PROJECT_ROOT}/packages/${MTLS_NAME}-${MTLS_VERSION}.tar.bz2")
set(MTLS_HASH "3ecf94fcfdaacafb757786a01b7538a61750ebd85c4b024f56ff8ba1490fcd38")

ExternalProject_Add(
  ${MTLS_NAME}
  PREFIX "${PROJECT_OUT}/${MTLS_NAME}"
  URL "${MTLS_PACKAGE}"
  URL_HASH SHA256=${MTLS_HASH}
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
    "${PROJECT_ROOT}/packages/patchs/${MTLS_NAME}-${MTLS_VERSION}/library/CMakeLists.txt" "${PROJECT_OUT}/${MTLS_NAME}/src/${MTLS_NAME}/library/"
  BUILD_IN_SOURCE
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DENABLE_PROGRAMS=OFF -DENABLE_TESTING=OFF -DCMAKE_INSTALL_PREFIX=${PROJECT_OUT}
)
